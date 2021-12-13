#include <iostream>
#include <string>
#include <fstream>
#include <random>


void createArrayFile(std::string fileName, uint32_t size){
	//generador de numero aleatoreos
	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_int_distribution<> unif(0,32000);

	//creacion y llenado de archivo
	std::ofstream outfile("../"+fileName);	
	outfile << std::to_string(size) << std::endl;
	for(size_t i=0; i < size ; i++){
		outfile << std::to_string(unif(gen)) << std::endl;
	}
	outfile.close();

}

void uso(std::string pname)
{
	std::cerr << "Uso: " << pname << " --fname [FILENAME] --size [NUMBER]" << std::endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char** argv){
	std::string fileName;
	uint32_t size;
	//////////////////////////////////////////
	//  Read command-line parameters easy way
	if(argc != 5){
		uso(argv[0]);
	}
	std::string mystr;
	for (size_t i=0; i < argc; i++) {
		mystr=argv[i];
		if (mystr == "--fname") {
			fileName = argv[i+1];
		}
		if(mystr == "--size"){
			size = std::stoi(argv[i+1]);
		}
	}
	
	createArrayFile(fileName, size);

	return 0;
}

