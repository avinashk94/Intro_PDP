#!/usr/bin/env bash

echo "Provisioning..."
date > /etc/vagrant_provisioned_at

# Install C/C++, OpenMP and MPI support
apt-get -y install build-essential
apt-get -y install cmake
apt-get -y install clang
apt-get -y install gdb
apt-get -y install valgrind
apt-get -y install mpich

# Install Java, Scala and Apache Spark
apt-get -y install default-jdk
apt-get -y install scala
wget -c https://d3kbcqa49mib13.cloudfront.net/spark-2.2.0-bin-hadoop2.7.tgz -P /opt
cd /opt/; tar xfz spark-2.2.0-bin-hadoop2.7.tgz; chown -R root:root spark-2.2.0-bin-hadoop2.7; cd

# Install NVIDIA CUDA
wget -c https://developer.nvidia.com/compute/cuda/8.0/Prod2/local_installers/cuda-repo-ubuntu1604-8-0-local-ga2_8.0.61-1_amd64-deb -P /opt
cd /opt/; ln -f -s cuda-repo-ubuntu1604-8-0-local-ga2_8.0.61-1_amd64-deb cuda-repo-ubuntu1604-8-0-local-ga2_8.0.61-1_amd64.deb; dpkg -i ./cuda-repo-ubuntu1604-8-0-local-ga2_8.0.61-1_amd64.deb; cd
apt-get update
apt-get -y install nvidia-cuda-toolkit lightdm-

# Clean apt-get
apt-get clean

echo "done!"
