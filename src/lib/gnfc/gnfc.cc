/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * GnF - Go & Flash is an Open Source tool for building the ISO images on linux systems
 * Licensed under the MIT License
 * Check out the README.md file for more informatio
*/

// This is the main file for making everything working with gnfc

// Source starts from here


#ifndef GNFC
#define GNFC 1

#include "gnfc_locals.hh"

int main(int argc, char* argv[])
{
    if (argc == 1) gnfc::error("Insufficient arguments were [passed] to gnfc\n Needed 3 arguments [gnfc image_path device]");
    else if (argc == 2 or argc == 3 or argc == 4){
        if (std::string(argv[1]) == "--version") std::cout<<"GNFC - Go & Flash CLI 1\n";
        else if (std::string(argv[1]) == "--help") std::cout<<"GNFC - Go & Flash CLI 1 docs\n"
                                                              <<"**Be sure to run gnfc as sudo as disk partitioning needs the sudo previllages**\n\n"
                                                              <<"Usage :- gnfc --version : Shows the version of gnfc\n"
                                                              <<"         gnfc --help    : Shows the docs\n"
                                                              <<"         gnfc --format  : Asks the the disk name and then formats it into ext4 fs."
                                                              <<"         gnfc --burn    : Asks for the image and device and then flashes the image into that device (Can be used to create bootable usb sticks).";
        
        else if (std::string(argv[1]) == "--format") {
            if (argc == 2) gnfc::error("Formating needs one more argument, The disk path eg /dev/sdX, Please Replace sdX with the actual device name\n");
            else gnfc::format_Drive(std::string(argv[2]));
        }
        else if (std::string(argv[1]) == "--burn") {
            if (argc == 2) gnfc::error("Burning needs two more argument, [The Path to the image file] and The disk path eg /dev/sdX, Please Replace sdX with the actual device name\n");
            if (argc == 3) gnfc::error("Burning needs one more argument, The disk path eg /dev/sdX, Please Replace sdX with the actual device name\n");
            else gnfc::burn(std::string(argv[2]), std::string(argv[3]));
        }
        else gnfc::error("Invalid command\n");
    }
}

#endif