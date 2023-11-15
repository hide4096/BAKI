set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g -std=c++17")
set(COMPONENT_ADD_INCLUDEDIRS
    "."
    "include"
)
set(COMPONENT_SRCS 
    "main.cpp"
    "peripheral.cpp"
    "PCA9632.cpp"
    "MPU6500.cpp"
    "Buzzer.cpp"
    "Motor.cpp"
    "adc.cpp"
    )
register_component()