
#include "../lib/main.hpp"
#include "../lib/util.hpp"
#include "../lib/fileSave.hpp"
#include "../lib/component.hpp"
#include "../lib/userComponent.hpp"
#include "../lib/chemicalComponent.hpp"
#include "../lib/logComponent.hpp"
#include "../lib/userLogComponent.hpp"
#include "../lib/chemicalLogComponent.hpp"

using namespace CLMS;

int main(int argc, char** argv) {
    // creating all the folders required by the project
    // all the folders will be created at initial run of the project
    std::filesystem::create_directories(Dir);
    std::filesystem::create_directories(std::string(Dir) + "\\log");
    std::filesystem::create_directories(std::string(Dir) + "\\log\\user");
    std::filesystem::create_directories(std::string(Dir) + "\\log\\chemical");
    std::filesystem::create_directories(std::string(Dir) + "\\component");
    std::filesystem::create_directories(std::string(Dir) + "\\component\\user");
    std::filesystem::create_directories(std::string(Dir) + "\\component\\chemical");
    
    system("cls");
    int option;
    const int quit = 4;
    UserComponent userComp = UserComponent();
    ChemicalComponent chemicalComp = ChemicalComponent();
    UserLogComponent userLogComp = UserLogComponent();
    ChemicalLogComponent chemicalLogComp = ChemicalLogComponent();

    do {
        std::cout << "1> Insert Data, 2> View Data, 3> Saving Data, 4> Quit\n";
        std::cin >> option;
        // option = 4;
        switch (option) {
            case 1: {
                std::cout << "1> User 2> userLog 3> Chemical 4> ChemicalLog\n";
                std::cin >> option;
                if (option == 1) {
                    userComp.getComponentInput();
                }else if (option == 2) {
                    userLogComp.getComponentInput();
                }else if (option == 3) {
                    chemicalComp.getComponentInput();
                }else if (option == 4) {
                    chemicalLogComp.getComponentInput();
                }
                option = 0;
            }; break;
            case 2: {
                std::cout << "1> User 2> userLog 3> Chemical 4> ChemicalLog\n";
                std::cin >> option;
                std::vector<std::string> headers, ids;
                std::string id;
                std::vector<std::vector<std::string>> data;
                std::cout << "Enter the id for single entry or single random char for all entries: " ;
                std::cin >> id;
                if (id.size() == 1) {
                    ids = {};
                }else {
                    ids = {id};
                }
                if (option == 1) {
                    data = userComp.getData(ids);
                    headers = userComp.getHeaders();
                }else if (option == 2) {
                    data = userLogComp.getData(ids);
                    headers = userLogComp.getHeaders();
                }else if (option == 3) {
                    data = chemicalComp.getData(ids);
                    headers = chemicalComp.getHeaders();
                }else if (option == 4) {
                    data = chemicalLogComp.getData(ids);
                    headers = chemicalLogComp.getHeaders();
                }
                for (std::string head : headers) {
                    std::cout << head << "\t";
                }
                std::cout << "\n";
                for (std::vector<std::string> usrD : data) {
                    for (std::string dat : usrD) {
                        std::cout << dat << "\t";
                    }
                    std::cout << "\n";
                }
                option = 0;
            }; break;
            case 3: {
                std::cout << "1> User 2> userLog 3> Chemical 4> ChemicalLog\n";
                int fileType, temp;
                std::cin >> option;
                std::vector<std::string> headers, ids;
                std::cout<<"1> Json, 2> CSV, 3> TSV\n";
                std::cin>>fileType;
                std::vector<std::vector<std::string>> data;
                std::string id;
                std::cout << "Enter the id for single entry or single random char for all entries: " ;
                std::cin >> id;
                if (id.size() == 1) {
                    ids = {};
                }else {
                    ids = {id};
                }
                if (option == 1) {
                    data = userComp.getData(ids);
                    headers = userComp.getHeaders();
                }else if (option == 2) {
                    data = userLogComp.getData(ids);
                    headers = userLogComp.getHeaders();
                }else if (option == 3) {
                    data = chemicalComp.getData(ids);
                    headers = chemicalComp.getHeaders();
                }else if (option == 4) {
                    data = chemicalLogComp.getData(ids);
                    headers = chemicalLogComp.getHeaders();
                }
                FileType ft;
                if(fileType == 1)
                    ft = FileType::JSON;
                else if(fileType == 2)
                    ft = FileType::CSV;
                else if(fileType == 3)
                    ft = FileType::TSV;
                else{
                    std::cout<<"Invalid file type"<<std::endl;
                    option = 0;
                    break;
                }
                FileSave fs(std::to_string(getCurrentTime()), ft, headers);
                for(auto d : data)
                {
                    fs.writeData(d);
                }
                option = 0;
            }; break;
        }
    } while (option != quit);
    return 0;
}
