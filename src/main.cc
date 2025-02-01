/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * GnF - Go & Flash is an Open Source tool for building the ISO images on linux systems
 * Licensed under the MIT License
 * Check out the README.md file for more informatio
*/

// This is the main file for making everything working

// Source starts from here

#include "link.hh"

int main(){
    HTMLUI root("Go & Flash - Stable (v1)", 900, 700);
    gnf::init_ui_data();
    root.loadHTML(gnf::ui_data);

    // Gnf Hybrid API
    std::string gnfConfig_Image_File,
                gnfConfig_Device_Path;
    root.registerFunction("GNF_makeConfig_InitImage", [&gconfig = gnfConfig_Image_File, &ROOT=root](std::string image_path){
        gconfig = image_path;
        std::cout<<"Image file was set to "<<gconfig<<"\n";
        std::ifstream ifile (gconfig);
        if (ifile.is_open()){
            
        }
        else {
            ROOT.executeJS("makeDefault(`Error -> The Image file ${image_on_flash} was not found`)");
        }
        ROOT.executeJS("setProgress(10, 'Initialising the Device name...')");
        ROOT.executeJS("window.webkit.messageHandlers.nativeCallback.postMessage('GNF_makeConfig_InitDevice:'+device_on_flash)");
    });


    root.registerFunction("GNF_makeConfig_InitDevice", [&gconfig = gnfConfig_Device_Path, &ROOT=root](std::string device_name){
        gconfig = device_name;
        ROOT.executeJS("setProgress(20, 'Un-mounting the Device...')");
        std::cout<<"Device Name was set to "<<gconfig<<"\n";

        // Command for unmounting the media
        std::system(std::string("umount " + device_name + "*").c_str());

        ROOT.executeJS("setProgress(40, 'Formating the Device With EXT4 FS..., The GUI Will Freeze for a while but please don\\'t close the window as the processing is held in the background')");
        ROOT.executeJS("makeFs();");

    });


    root.registerFunction("GNF_makeFs", [&DEV=gnfConfig_Device_Path, &ROOT=root](std::string arg){

        // command for making an ext4 file system 
        std::system(std::string("echo y | mkfs.ext4 " + DEV + "").c_str());
        ROOT.executeJS("setProgress(80, 'The Image is being written to the device. The GUI will be freezed untill the processing reaches the 100%. During that please don\\'t close the window at any cost, Your device may become un-usable.')");
        ROOT.executeJS("writeIMG();");
    });


    root.registerFunction("GNF_burn", [&IMG=gnfConfig_Image_File, &DEV=gnfConfig_Device_Path, &ROOT=root](std::string arg){
        // command for making an ext4 file system 
        std::system(std::string("dd if=" + IMG + " of=" + DEV + " status=progress").c_str());
        ROOT.executeJS("setProgress(100, 'The Image Is Flashed! Congratulations!!! Now You can use it how ever you want.')");
        ROOT.executeJS("makeDefault(`The Image Is Flashed! Congratulations!!! Now You can use it how ever you want.`)");
    });

        root.executeJS("var a = 90;");

    root.run();
};