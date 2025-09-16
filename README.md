![Screenshot of Wet Onion Soup](https://raw.githubusercontent.com/ismaelvazquez182/Wet-Onion-Soup/refs/heads/main/wet-onion-soup-screenshot.png)

# Development Stopped
Demi has implemented a much cleaner solution to re-enable guild functionality inside of Well of Souls. As such, development on this project will be coming to an end.

This was a fun project and I learned quite a bit. There were so many things that I hadn't considered when originally deciding to tackle this problem. I had to do some reverse engineering to find the proper memory locations to modify. Then I had to try and limit the release of that information to prevent would be bad actors. 

Aside from the reverse engineering, a lot of security concerns began popping up as I thought of ways to secure the server from attacks. While I never got to implement those ideas, it was an interesting thought activity. It made me appreciate the work that the creator of the game put in. I also found a new appreciation for some of his design choices. Something as simple as this began feeling like a monumental feat and he did this and much much much more. Kudos to you, Dan! If you're reading this by any chance, thank you for being one of the better parts of my childhood.

Alright, less I digress anymore - let me tell you about some of the other challenges I had. Before this project, I had never touched ImGui... The example code that comes in the library is overwhelming to say the least. Surprisingly though, using it was a blast! Everything began to feel intuitive and elgant. I will definitely be using more of it in the future. Ah, github/git. Normally, I work on simple projects and then I post them on github to never touch again. This was different. I ended up cloning the repo in my development server and got to learn about setting up guthub with SSH. Pretty cool stuff. 

Reverse engineering, Windows OS, C++, Linux, Git, Imgui, REST API, Golang, SDL, Windows + WinHTTP API... those are just some of the buzzwords that embodied this project. Until the next one, thanks for checking out my project. Later.

## Basic Build Instructions
* [Download SDL3 Devel 3.2.22](https://github.com/libsdl-org/SDL/releases/download/release-3.2.22/SDL3-devel-3.2.22-VC.zip) and unzip the folder to your C drive. Rename the root folder to SDL3. 
* [Download ImGui v1.92.2b](https://github.com/ocornut/imgui/archive/refs/tags/v1.92.2b.zip) and unzip the folder to your C drive. Rename the root folder to imgui. 
* You will also need the Windows 11 SDK. You can get the Windows SDK in two ways: install it from [here](https://go.microsoft.com/fwlink/?linkid=2332022) or by selecting “Windows 11 SDK (10.0.26100.0)” in the optional components of the Visual Studio 2022 Installer. (I recommend installing it from the Visual Studio installer.
