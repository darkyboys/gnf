/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * GnF - Go & Flash is an Open Source tool for building the ISO images on linux systems
 * Licensed under the MIT License
 * Check out the README.md file for more informatio
*/

// This is the for creating & Managing the UI Components

// Source starts from here

namespace gnf {
    std::string ui_data; // the variable for holding the ui in the memory
    void init_ui_data(){ // the function for initalising the final ui
        ui_data =  "<style>"
                   "    body{"
                   "        background-color: white;"
                   "        color: #1C1C1C;"
                   "    }"
                   "    button{"
                   "        background-color: rgb(235, 244, 251);"
                   "        color: #1C1C1C;"
                   "        padding: 5px 20px;"
                   "        border: 1px solid rgb(68, 158, 227);"
                   "        border-radius: 5px;"
                   "        cursor: pointer;"
                   "        transition: 0.2s;"
                   "    }"
                   "    button:hover{"
                   "        background-color: rgb(202, 232, 255);"
                   "    }"
                   "    button:active{"
                   "        background-color: rgb(158, 213, 255);"
                   "    }"
                   "    input{"
                   "        border: 0px;"
                   "        border-bottom: 2px solid rgb(68, 158, 227);"
                   "        padding: 5px 20px;"
                   "        color: #1C1C1C;"
                   "        outline: none;"
                   "        width: 300px;"
                   "        border-radius: 2px;"
                   "    }"
                   "    #progress_bar{"
                   "        height: 50px;"
                   "        width: 300px;"
                   "        border: 5px solid white;"
                   "        outline: 1px solid rgb(68, 158, 227);;"
                   "        display: flex;"
                   "        align-items: center;"
                   "        justify-content: left;"
                   "    }"
                   "    #progress{"
                   "        height: 50px;"
                   "        width: 0%;"
                   "        background: rgb(158, 213, 255);"
                   "        animation-name: fade;"
                   "        animation-iteration-count: infinite;"
                   "        animation-direction: alternate;"
                   "        animation-duration: 1s;"
                   "        display: flex;"
                   "        color: dimgray;"
                   "        align-items: center;"
                   "        justify-content: center;"
                   "        transition: 1s;"
                   "    }"
                   "    @keyframes fade{"
                   "        from{background:rgb(158, 213, 255);}"
                   "        to  {background:rgb(202, 232, 255);}"
                   "    }"
                   "</style>"
                   "<body>"
                   "    <center>"
                   "        <h1>Go & FLash</h1>"
                   "        <h6>A Simple & Open Source Image Flasher</h6>"
                   "        <br><br>"
                   "        <input placeholder=\"Path yo your '.iso' file\" id='iso'><br><br>"
                   "        <input placeholder=\"Path yo your device eg '/dev/sda' etc.\" id='device'><br><br>"
                   "        <br><br>"
                   "        <button onclick='flashWarning()'>Start Flashing</button>"
                   "        <br><br><br><br>"
                   "        <div id='temp'></div>"
                   "    </center>"
                   "</body>";

                //    Javascript
                ui_data += R"(<script>
                                let is_processing = false;
                                let image_on_flash, device_on_flash;
                                function flashWarning(){
                                    if (is_processing) alert('The Image ' + image_on_flash + ' is already flashing to the device ' + device_on_flash + ', You can only proceed once they are done.');
                                    else {
                                        let conf = confirm("Are you sure that the device at '" + document.getElementById("device").value + "' is the exact device where you want to flash the iso image file? \nBecause doing this will erase the entire existing data on the device so be sure that you are sure about the device.");
                                        if (conf) startFlashing();
                                    }
                                }

                                function setProgress(value, message){
                                    document.getElementById('progress').innerHTML = value+"%";
                                    document.getElementById('progress').style.width = value+"%";
                                    document.getElementById('state').innerHTML = message;
                                }

                                function makeDefault(message){
                                    alert (message);
                                    document.getElementById('temp').innerHTML = "";
                                    image_on_flash = "";
                                    device_on_flash = "";
                                    is_processing = false;
                                }

                                function makeFs(){
                                    setTimeout(()=>{
                                        window.webkit.messageHandlers.nativeCallback.postMessage('GNF_makeFs:mkfs.ext4');
                                    }, 1000);
                                }

                                function writeIMG(){
                                    setTimeout(()=>{
                                        window.webkit.messageHandlers.nativeCallback.postMessage('GNF_burn:iso-image-file');
                                    }, 2000);
                                }

                                function startFlashing(){
                                    image_on_flash = document.getElementById('iso').value;
                                    device_on_flash = document.getElementById('device').value;
                                    if (image_on_flash == ""){
                                        alert("Please provide an image path");
                                    }
                                    else if (device_on_flash == ""){
                                        alert ("Please provide a device path eg '/dev/sda' be sure to provide the exact device path where you want to flash the iso.");
                                    }
                                    else {
                                        is_processing = true;
                                        document.getElementById('temp').innerHTML = `<h5>Please open the program via terminal to view more detailed logs, Or see the high level processings.</h5><h5 id='state'>Initialising the File</h5><div id='progress_bar'><div id='progress'>0%</div></div>`;
                                        window.webkit.messageHandlers.nativeCallback.postMessage("GNF_makeConfig_InitImage:"+image_on_flash);
                                    }
                                }
                            </script>
                            )";
    }
};