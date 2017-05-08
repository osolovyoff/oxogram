#include <string.h>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#if defined(RPI)
#include <unistd.h>
#include <fcntl.h>

#include <net/if.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/error.h>
#endif

class CanLinux
{
public:
    static const size_t MAX_FRAME_DATA_SIZE = 8U;

public:
	explicit CanLinux(const char* port = "can0");
	virtual ~CanLinux();
	
	bool open(bool set_timeout = false, int64_t timeout_sec = 0,
		int64_t timeout_micro = 50'000);
	
	void write_frame(const int32_t id, void* data, const std::size_t len);
	void read_frame(void* out_data, std::size_t& out_len, uint32_t& out_id);
	
protected:
	const char* get_port() const { return _port.c_str(); }
	
private:
    std::string _port;
	int         _handle;
};