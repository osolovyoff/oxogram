#include "can_linux.h"

CanLinux::CanLinux(const char* port /* = "can0" */)
    : _port(port)
{
}

CanLinux::~CanLinux()
{
#if defined(RPI)
    close(_handle);
#endif
}

bool CanLinux::open(bool set_timeout, int64_t timeout_sec, int64_t timeout_micro)
{
#if defined(RPI)
    struct sockaddr_can _addr;
    struct ifreq        _ifr;

    _handle = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (_handle < 0)
    {
        printf("%s socket error %s", _port.c_str(), strerror(errno));
        return false; // socket error
    }

    strcpy(_ifr.ifr_name, _port.c_str());

    const int err_ioctl = ioctl(_handle, SIOCGIFINDEX, &_ifr);
    if (err_ioctl < 0)
    {
        printf("%s error io control! %s\n", _port.c_str(), strerror(errno));
        return false;
    }

    
    _addr.can_family = AF_CAN;
    _addr.can_ifindex = _ifr.ifr_ifindex;

    if (!_addr.can_ifindex)
    {
        printf("%s invalid bridge interface ! %s\n", _port.c_str(), strerror(errno));
        return false;
    }

    if (set_timeout)
    {
        struct timeval tv;
        tv.tv_sec = timeout_sec;
        tv.tv_usec = timeout_micro;
        const auto err_opt = setsockopt(_handle, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(struct timeval));
        if (err_opt != 0)
        {
            printf("%s error options! %s\n", _port.c_str(), strerror(errno));
            return false;
        }
    }


    int recv_own_msgs = 0; /* 0 = disabled (default), 1 = enabled */
    const auto err_recv_own = setsockopt(_handle, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &recv_own_msgs, sizeof(recv_own_msgs));
    if (err_recv_own != 0)
    {
        printf("%s error receive own message! %s\n", _port.c_str(), strerror(errno));
        return false;
    }

    const int err_bind = bind(_handle, (struct sockaddr*)&_addr, sizeof(_addr));
    if (err_bind < 0)
    {
        printf("%s error bind! %s\n", _port.c_str(), strerror(errno));
        return false;
    }

    fcntl(_handle, F_SETFL, O_NONBLOCK);

#endif
    return true;
}

void CanLinux::write_frame(const int32_t id, void* data, const std::size_t len)
{
#if defined(RPI)
    struct can_frame frame;
    memset(&frame, 0, CAN_MTU);

	frame.can_dlc = len;
	frame.can_id = id;

    memcpy(frame.data, data, len);
    const int received_bytes = write(_handle, &frame, CAN_MTU);
    if (received_bytes < 0)
    {
		printf("Oh dear, something went wrong with send! %s\n", strerror(errno));
    }
#else
    const uint8_t* p = static_cast<uint8_t*>(data);
    printf("  %s  %003x   [%d]", _port.c_str(), id, len);
    for (size_t i = 0; i < len; ++i)
        printf(" %02x", (int)p[i]);
    printf("\n\r");
#endif
}

void CanLinux::read_frame(void* out_data, std::size_t& out_len, uint32_t& out_id)
{
#if defined(RPI)
    struct can_frame frame;
    const int received_bytes = ::read(_handle, &frame, CAN_MTU);
    if (received_bytes <= 0)
    {
        //printf("Oh dear, something went wrong with dump! %s\n", strerror(errno));
        return;
    }
    out_id = frame.can_id;
    out_len = frame.can_dlc;
    memcpy(out_data, frame.data, out_len);
#endif
}