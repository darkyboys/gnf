/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * GnF - Go & Flash is an Open Source tool for building the ISO images on linux systems
 * Licensed under the MIT License
 * Check out the README.md file for more informatio
*/

// This is the file for including the Headers for gnfc

// Source starts from here

// Std Cxx17 Headers

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <system_error>

// namespace for gnfc
namespace gnfc {
    int confirm(std::string message){
        int rval = 0;
        char temp;
        while (1){
            std::cout<<message<<" (y/n) ";
            std::cin>>temp;
            if (temp == 'y' or temp == 'Y'){ rval = 1; break; }
            else if (temp == 'n' or temp == 'N'){ rval = 0; break; }
            else std::cout<<"Invalid character! Please try again.\n";
        }
        return rval;
    }

    void error(std::string message){
        std::cout<<"\e[0;30m"<<message<<"\e[0;37m\n";
        std::exit ( 3 );
    }

    void format_Drive(std::string drive_name){
        if (!confirm("Are you sure ? Because doing this will erase all the data from your drive <" + drive_name + "> and you won't be able to revert the changes!")){
            std::cout<<"Aborting the process.\n";
            std::exit ( 3 );
        }
        std::cout<<"Umounting the device for device formatting\n";
        std::system(std::string("umount " + drive_name + "*").c_str());
        std::cout<<"Using the mkfs.ext4! for device formatting\n";
        std::system(std::string("echo y | mkfs.ext4 " + drive_name).c_str());
    }

    void burn(std::string imagePath, std::string device){
        std::ifstream ifile_iso_image (imagePath);
        if (!ifile_iso_image.is_open()){
            error("Error -> Fatal (The Image File not found)");
        }
        format_Drive(device); // format the drive first
        std::system(std::string("dd if=" + imagePath + " of=" + device + " status=progress").c_str());
        std::cout<<"Your ISO Is Burned / Flash and now you can absolutely use it for any purposes you want.\n";
    }
};