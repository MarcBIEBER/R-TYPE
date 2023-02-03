[![GitHub Super-Linter](https://github.com/EpitechPromo2025/B-CPP-500-MLH-5-1-rtype-arnaud.issoire/workflows/Lint%20Code%20Base/badge.svg)](https://github.com/marketplace/actions/super-linter)

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#authors">Authors</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

R-Type is an Epitech project during 3rd years.
In this project we need to create a game with our own Game Engine.
We use a specific architecture who is ECS (Entity-Component-System)

Here's why:
* ECS is specifically for the game
* Better performance
* More scalability to grow up the project


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started
<!-- 
### Prerequisites

* Install Cmake packages (Exemple on Fedora)
  ```sh
    sudo dnf install cmake
  ``` -->

### Installation
#### On Linux (Fedora) / MacOs

  If you are on other linux os you have to download yourself cmake and libX11 and do not use build.sh but `cmake .`

  1. Clone the repo
   ```sh
    git clone --recurse-submodules https://github.com/EpitechPromo2025/B-CPP-500-MLH-5-1-rtype-arnaud.issoire.git
   ```
  2. Run `build.sh`
   ```sh
    ./build.sh
   ```

  3. Run `binary`
  ```sh
      ./r-type_client
      ./server-binary <port>
  ```

#### On Windows
  1. Clone the repo
  ```sh
    git clone --recurse-submodules https://github.com/EpitechPromo2025/B-CPP-500-MLH-5-1-rtype-arnaud.issoire.git
  ```
  2. Run `build.sh`
  ```sh
    ./build.sh
    Or Double click on it
  ```
  3. Run `r-type_client.sln` file
  ```sh
    Open the r-type_client.sln file with Visual Studio
  ```
  4. Set in Realase mode
  
  5. Click on execute

  6. En error can appear, just click on `Yes` and run `windows_move.sh`
  ```sh
    ./windows_move.sh
    Or Double click on it
  ```
  7. Click on execute again
  8. Run the binary in realase folder in the root of the project
  ```sh
    ./r-type_client
    Or Execute the binary with Administrator mode

    The server can only be run with ./server-binary <port>
  ```

## Packages on Linux

1. Run `./build.sh`
2. Run `sudo make package`
3. You can find the package in the _CPack_Packages/Linux/
4. Run the created `.sh` file at the root of the repository

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## If you just want to play the game

1. Clone the repo
2. Run the `Game_Setup.msi` in the folder windows_installer and follow the instructions

<!-- USAGE EXAMPLES -->
## Usage

_Please refer to the [Documentation](https://marcbieber.github.io/DocRType/)_

Also you can see the the template created for you in the [Template](./Template/README.md) folder to get more information about the project.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "newFeature".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Authors

👤 **Marc Bieber**


👤 **Jermey Chenet**


👤 **Arnaud Issoire**


## Acknowledgments

* [README Template](https://github.com/othneildrew/Best-README-Template)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- 
Exemple :  supported platforms, troubleshooting section, detailed build instructions
-->
