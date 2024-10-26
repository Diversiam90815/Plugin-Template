cmake_minimum_required(VERSION 3.25)

project(AudioPlugin VERSION 0.1.0)

set (SOURCE_FILES_DIR ${PROJECT_SOURCE_DIR}/Source)
set (HEADER_FILES_DIR ${PROJECT_SOURCE_DIR}/include)

# Add the plugin target
juce_add_plugin(${PROJECT_NAME}
                COMPANY_NAME "DiversiamProduction"
                PLUGIN_CODE IOTO
                IS_SYNTH FALSE
                NEEDS_MIDI_INPUT FALSE
                NEEDS_MIDI_OUTPUT FALSE
                FORMATS VST3 Standalone
                PLUGIN_MANUFACTURER_CODE 3160
                PRODUCT_NAME "${PROJECT_NAME}"
)

# Generate the JuceHeader.h
# juce_generate_juce_header(${PROJECT_NAME})


#-----------------------------------------------------------------------------------------
# Files
#-----------------------------------------------------------------------------------------

set(Header_Files
        ${HEADER_FILES_DIR}/PluginProcessor.h
        ${HEADER_FILES_DIR}/PluginEditor.h
        
        ${HEADER_FILES_DIR}/Parameters.h
)

set(Source_Files
         ${SOURCE_FILES_DIR}/PluginProcessor.cpp
         ${SOURCE_FILES_DIR}/PluginEditor.cpp
)

source_group("Source Files" FILES ${Source_Files})
source_group("Header Files" FILES ${Header_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

target_sources(${PROJECT_NAME} PRIVATE  
        ${ALL_FILES} 
)


target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${SOURCE_FILES_DIR}
        ${HEADER_FILES_DIR}
)


target_compile_definitions(${PROJECT_NAME} PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_USE_WINDOWS_MEDIA_FORMAT=1
        JUCE_LOAD_CURL_SYMBOLS_LAZILY=1
        JUCE_WASAPI=1
        JUCE_DIRECTSOUND=1
        JUCE_ASIO=0
        JUCE_USE_ANDROID_OBOE=1
        JUCE_USE_OBOE_STABILIZED_CALLBACK=1
        -DENV_DEVELOPMENT
        _CRT_SECURE_NO_WARNINGS
)


set (PROJECT_LIBS juce::juce_audio_utils
                  juce::juce_audio_plugin_client
                  juce::juce_core
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBS} )

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
                /Oi;
                /Gy
        >
        $<$<CONFIG:Debug>:
                /Od;
                /Z7
        >
        /sdl
        /MP
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
)

# Suppress specific compiler warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    /wd4146  # Suppress warning C4146
)