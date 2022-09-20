//
// Created by bia on 11/05/2022.
//

#include <fstream>
#include "FileRepository.h"
#include "RepositoryException.h"


FileRepository::FileRepository(const FileRepository &other) : Repository(other)
{
    this->filename = other.filename;
    loadFromFile();
}

FileRepository::FileRepository(const std::string &filename) : Repository(filename) {
    this->filename = filename;
    this->loadFromFile();
}


FileRepository::~FileRepository(){
}

void FileRepository::loadFromFile()
{
    std::ifstream f(this->filename);

    if (!f.is_open())
        throw FileException("	The file could not be opened!\n");

    std::string temp;
    std::vector<std::string> args;

    while (!f.eof())
    {
        std::getline(f, temp);
        if (f.eof() || temp.empty())
        {
            f.close();
            break;
        }

        std::string sep = "|-:";
        args = explode(temp, sep);
        Event e;
        e.setTitle(args[0]);
        e.setDescription(args[1]);
        Date d = {std::stoi(args[2]), std::stoi(args[3]), std::stoi(args[4]), std::stoi(args[5]), std::stoi(args[6])};
        e.setDate(d);
        e.setNumberOfPeople(std::stoi(args[7]));
        e.setLink(args[8]);
        addEvent(e);
    }

    f.close();
}
//
//int FileRepository::addEvent(const Event& eventToAdd)
//{
//    auto iteratorWhereEventIsFound = getPos(eventToAdd);
//    if (iteratorWhereEventIsFound != -1)
//        return -1;
//    eventList.push_back(eventToAdd);
//    this->saveToFile();
//    return 1;
//}

void FileRepository::saveToFile()
{
    if (this->eventFileName.empty())
        return;
    std::ofstream fout(this->eventFileName);
    for (const Event& eventToWrite : this->eventList) {
        fout << eventToWrite.getOutputFormat() << '\n';
    }
    fout.close();
}

FileRepository& FileRepository::operator=(const FileRepository& other)
{
    if (this == &other)
        return *this;
    Repository::operator=(other);
    this->filename = other.filename;

    return *this;
}

