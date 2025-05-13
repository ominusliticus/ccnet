#!/bin/bas

mkdir -p $HOME/opt
export OPT=$HOME/opt

# Installing Intel OneAPI

# WSL installation requirements
install_wsl2_requirements () {
    # package repository
    sudo apt-get install -y gpg-agent wget
    wget -qO - https://repositories.intel.com/graphics/intel-graphics.key | sudo gpg --dearmor --output /usr/share/keyrings/intel-graphics.gpg
    echo 'deb [arch=amd64 signed-by=/usr/share/keyrings/intel-graphics.gpg] https://repositories.intel.com/graphics/ubuntu focal-devel main' | sudo tee  /etc/apt/sources.list.d/intel.gpu.focal.list
    sudo apt update

    # Install runtime devel
}

install_intelOneAPI () {
    # oneAPI Base toolkit
    wget https://registrationcenter-download.intel.com/akdlm/IRC_NAS/cca951e1-31e7-485e-b300-fe7627cb8c08/intel-oneapi-base-toolkit-2025.1.0.651_offline.sh
    sh ./intel-oneapi-base-toolkit-2025.1.0.651_offline.sh -a --silent --eula accept --install-dir $OPT

    # HPC toolkit
    wget https://registrationcenter-download.intel.com/akdlm/IRC_NAS/d0df6732-bf5c-493b-a484-6094bea53787/intel-oneapi-hpc-toolkit-2025.1.0.666_offline.sh
    sh ./intel-oneapi-hpc-toolkit-2025.1.0.666_offline.sh -a --silent --eula accept --install-dir $OPT

    # C++ Essentials
    wget https://registrationcenter-download.intel.com/akdlm/IRC_NAS/0dbea6d6-0e62-4419-b68d-5d658677fce7/intel-cpp-essentials_2025.1.0.571_offline.sh
    sh ./intel-cpp-essentials_2025.1.0.571_offline.sh -a --silent --eula accept --install-dir $OPT

    # Fortran Essentials
    wget https://registrationcenter-download.intel.com/akdlm/IRC_NAS/306e03be-1259-4d71-848a-59e23013c4f0/intel-fortran-essentials_2025.1.0.556_offline.sh
    sh ./intel-fortran-essentials_2025.1.0.556_offline.sh -a --silent --eula accept --install-dir $OPT
}
