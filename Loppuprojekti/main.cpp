#include <Jolt/Jolt.h>

#include <iostream>

#include <raylib-cpp.hpp>

#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

int main(int, char**){
    std::cout << "Hello, from Loppuprojekti!\n";

    JPH::RegisterDefaultAllocator();

    JPH::Factory::sInstance = new JPH::Factory();

    std::cout << "JPH worksish?";

}
