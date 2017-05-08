//#include "package_observer.h"
//
//#include "neuro/develop/logger/logger.h"
//
//void PackageObserver::subscribe(const PackageIndex index, Listener fn)
//{
//    std::lock_guard<std::mutex> lock(_mutex);
//    
//    const auto& it = _listeners.find(index);
//    if (it == _listeners.end())
//        _listeners.emplace(std::move(index), fn);
//    else
//    {
//        logger
//            << Log::Type::error
//            << logger.time_now()
//            << CODEINFO
//            << "Dublicate listener function, index package:"
//            << (int)index.get_module_index()
//            << " "
//            << (int)index.get_command_index()
//            << std::endl;
//    }
//}
//
//void PackageObserver::broadcast(Package && package) const
//{
//	const auto& it = _listeners.find(package.get_index());
//	if (it != _listeners.end())
//	{
//        logger
//            << Log::Type::info
//            << CODEINFO
//            << "Module_index="
//            << (int)it->first.get_module_index()
//            << "Command index="
//            << (int)it->first.get_command_index()
//            << " size=" << package.size() << " bytes"
//            << std::endl;
//
//		it->second(std::move(package));
//	}
//    else
//    {
//        logger
//            << Log::Type::error
//            << logger.time_now()
//            << CODEINFO
//            << "Package index not found "
//            << "module: " << (int) package.get_index().get_module_index() << ' '
//            << "command: " << (int) package.get_index().get_command_index() << ' '
//            << std::endl;
//    }
//}