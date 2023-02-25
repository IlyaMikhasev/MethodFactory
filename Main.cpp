#include <iostream>
#include <memory>
class IParser {
	public:
		virtual ~IParser() {}
		virtual void readFile() = 0;
};
class JSON_parser : public IParser {
public:
	void readFile() override{
		std::cout << "JSON parsing\n";
	}

};
class INI_parser : public IParser {
public:
	void readFile() override {
		std::cout << "INI parsing\n";
	}

};
class YAML_parser : public IParser {
public:
	void readFile() override {
		std::cout << "YAML parsing\n";
	}

};
class Reader {
public:
	void readFile() {
		std::shared_ptr<IParser> pars = parsingFile();
		pars->readFile();
	}
	virtual std::shared_ptr<IParser> parsingFile() = 0;
	virtual ~Reader() {}
};
class JSON_Reader : public Reader {
public:
	std::shared_ptr<IParser> parsingFile() override{
		return std::make_shared<JSON_parser>();
	}
};
class INI_Reader : public Reader {
public:
	std::shared_ptr<IParser> parsingFile() override {
		return std::make_shared<INI_parser>();
	}
};
class YAML_Reader : public Reader {
public:
	std::shared_ptr<IParser> parsingFile() override {
		return std::make_shared<YAML_parser>();
	}
};
int main() {
	setlocale(LC_ALL, "Russian");
	std::string config;
	std::shared_ptr<Reader> reader;
	std::cout << "Enter config JSON,INI,YAML\n-> ";
	std::cin >> config;
	if (config == "JSON") {
		reader = std::make_shared<JSON_Reader>();
	}
	else
		if (config == "INI") {
			reader = std::make_shared<INI_Reader>();
		}
		else
			if (config == "YAML") {
				reader = std::make_shared<YAML_Reader>();
			}
			else {
				throw "Error:unknown config\n";
			}
	reader->readFile();
	return 0;
}