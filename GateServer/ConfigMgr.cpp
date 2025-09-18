#include "ConfigMgr.h"
ConfigMgr::ConfigMgr() {
	boost::filesystem::path current_path = boost::filesystem::current_path();
	boost::filesystem::path config_path = current_path / "config.ini";
	std::cout << "Config path: " << config_path << std::endl; 
		// 使用Boost.PropertyTree来读取INI文件。将文件使用read方法，并且传入ptree中进行存储。之后使用图来进行另外的存储
	boost::property_tree::ptree pt ;
	boost::property_tree::read_ini(config_path.string(), pt);
	// 遍历INI文件中的所有section  
	for (const auto& section_pair : pt) {
		const std::string& section_name = section_pair.first;//读取功能，第一个结点
		const boost::property_tree::ptree& section_tree = section_pair.second;//对应的图，第二个结点
		//遍历第一层即每一个功能和其所对应的sectionmap图，接下来遍历每个功能的section
		// 对于每个section，遍历其所有的key-value对，读取每个键值，然后存入map中
		//创建图
		std::map<std::string, std::string> section_config;
		for (const auto& key_value_pair : section_tree) {
			const std::string& key = key_value_pair.first;
			const std::string& value = key_value_pair.second.get_value<std::string>();
			section_config[key] = value;
		}
		SectionInfo sectionInfo;//创建实例
		sectionInfo._section_datas = section_config;//将上面创建的map图作为参数传递进section中
		// 将section的key-value对保存到config_map中  
		_config_map[section_name] = sectionInfo;
	}
	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		SectionInfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value_pair : section_config._section_datas) {
			std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
		}
	}
}
