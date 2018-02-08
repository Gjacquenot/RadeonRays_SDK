
cp ./UnitTest/test_main.cpp                               t1.txt
cp ./RadeonRays/src/api/radeon_rays.cpp                   t2.txt
cp ./RadeonRays/src/device/embree_intersection_device.h   t3.txt
cp ./RadeonRays/src/device/embree_intersection_device.cpp t4.txt

cd 3rdparty
wget https://github.com/embree/embree/releases/download/v3.0.0-beta.0/embree-3.0.0.x86_64.macosx.tar.gz -O embree3.tgz
tar -xf embree3.tgz
cd ..
wget https://raw.githubusercontent.com/embree/embree/master/scripts/cpp-patch.py
wget https://raw.githubusercontent.com/embree/embree/master/scripts/embree2_to_embree3.patch

for i in `find . -name "*.h*" -o -name "*.c*"`; do grep embree $i;done

python cpp-patch.py --help
python cpp-patch.py --patch embree2_to_embree3.patch --in ./UnitTest/test_main.cpp --out ./UnitTest/test_main.cpp
python cpp-patch.py --patch embree2_to_embree3.patch --in ./RadeonRays/src/api/radeon_rays.cpp --out ./RadeonRays/src/api/radeon_rays.cpp
python cpp-patch.py --patch embree2_to_embree3.patch --in ./RadeonRays/src/device/embree_intersection_device.h --out ./RadeonRays/src/device/embree_intersection_device.h
python cpp-patch.py --patch embree2_to_embree3.patch --in ./RadeonRays/src/device/embree_intersection_device.cpp --out ./RadeonRays/src/device/embree_intersection_device.cpp
