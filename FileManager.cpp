#include "pch.h"
#include "FileManager.h"
#include <cstdio>

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

//std::vector<unsigned char> FileManager::ReadFromFile(const std::string& fileName)
//{
    //std::vector<unsigned char> buffer{};

    //FILE* pFile{ std::fopen(fileName.c_str(),"r") };//uit cstdio, c-string doorgeven

    //if (pFile) //nullptr check
    //{
    //    std::fseek(pFile, 0, SEEK_END); // 'cursor' opt einde

    //    long fileLength{ std::ftell(pFile) }; // voor lengte te weten door verschil eind begin

    //    buffer.resize(fileLength);

    //    //std::fseek(pFile, 0, SEEK_SET); // cursor in begin zetten
    //    std::rewind(pFile);

    //    // lezen zelf

    //    std::fread(buffer.data(), sizeof(unsigned char), fileLength, pFile); // data: pointer naar lijst, om alles te zetten

    //    std::fclose(pFile);
    //}

    //return buffer;

    

//}

//std::string FileManager::ReadFromTextFile(const std::string& fileName)
//{
//    auto buffer{ ReadFromFile(fileName) };
//    return std::string{ buffer.begin(), buffer.end() };
//}

/* CREDITS:
        hulp Liam */



