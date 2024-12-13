set(PAK_SOUND_DIR          "${PAK_DIR}/sound")
set(PAK_MODIFIED_SOUND_DIR "${PAK_MODIFIED_DIR}/sound")

set(JSOX                   "${PROJECT_SOURCE_DIR}/tools/sound/jsox.js")
set(GEN_SOUND_IDS          "${PROJECT_SOURCE_DIR}/tools/sound/generate_sound_ids.js")

cmake_path(
    RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR
    BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
    OUTPUT_VARIABLE RELATIVE_CURRENT_DIR
)

function(_get_localized_pak_sound_dir LANGUAGE DIR_OUT)
    if (LANGUAGE STREQUAL "english")
        set(${DIR_OUT} "${PAK_SOUND_DIR}")
    else()
        set(${DIR_OUT} "${PAK_DIR}/localized/${LANGUAGE}/sound")
    endif()

    return(PROPAGATE ${DIR_OUT})
endfunction()

function(_get_localized_sound_name SOUND_NAME LANGUAGE NAME_OUT)
    cmake_path(
        GET SOUND_NAME FILENAME
        SOUND_FILENAME
    )
    cmake_path(
        REPLACE_FILENAME SOUND_NAME
        "${LANGUAGE}_${SOUND_FILENAME}"
        OUTPUT_VARIABLE ${NAME_OUT}
    )

    return(PROPAGATE ${NAME_OUT})
endfunction()

#################
## Valve sound ##
#################

function(_add_extract_video_audio_command INPUT_FILE OUTPUT_FILE)
    cmake_path(
        GET OUTPUT_FILE PARENT_PATH
        OUTPUT_DIR
    )

    add_custom_command(
        DEPENDS
            ${INPUT_FILE}
        OUTPUT
            ${OUTPUT_FILE}
        COMMAND
            ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND
            ${FFmpeg_EXECUTABLE}
            -i ${INPUT_FILE} -vn -loglevel error -y ${OUTPUT_FILE}
        COMMENT
            "Extracting audio from $<PATH:RELATIVE_PATH,${INPUT_FILE},${PROJECT_SOURCE_DIR}>"
        VERBATIM
    )
endfunction()

_add_extract_video_audio_command(
    ${VALVE_INTRO_VIDEO}
    ${PAK_SOUND_DIR}/ambient/music/valve.wav
)

##########################
## Sound transformation ##
##########################

set(SOUND_SCRIPTS
    ambient/alarms/portal_elevator_chime.sox
    ambient/dinosaur_fizzle.sox
    ambient/machines/portalgun_rotate1.sox
    ambient/machines/ticktock1.sox
    ambient/machines/wall_move5.sox
    ambient/music/valve.sox
    buttons/button10.sox
    buttons/button3.sox
    common/wpn_denyselect.sox
    common/wpn_select.sox
    doors/door_metal_thin_close2.sox
    doors/doormove1.jsox
    doors/doormove2.sox
    plats/elevator_move_loop1.sox
    plats/elevator_stop1.sox
    player/footsteps/concrete1.sox
    player/footsteps/concrete2.sox
    player/footsteps/concrete3.sox
    player/footsteps/concrete4.sox
    player/portal_enter1.sox
    player/portal_enter2.sox
    player/portal_exit1.sox
    player/portal_exit2.sox
    player/suit_denydevice.sox
    ui/buttonclickrelease.sox
    ui/buttonrollover.sox
    vehicles/apc/apc_shutdown.sox
    vehicles/apc/apc_start_loop3.jsox
    vehicles/tank_turret_start1.sox
    vo/aperture_ai/ding_off.sox
    vo/aperture_ai/ding_on.sox
    weapons/cguard/charging.sox
    weapons/physcannon/energy_bounce1.sox
    weapons/physcannon/energy_disintegrate4.sox
    weapons/physcannon/energy_sing_explosion2.sox
    weapons/physcannon/energy_sing_flyby1.sox
    weapons/portalgun/portal_fizzle2.sox
    weapons/portalgun/portal_open2.sox
    weapons/portalgun/portalgun_shoot_blue1.sox
    weapons/portalgun/portalgun_shoot_red1.sox
    weapons/stunstick/alyx_stunner1.sox
)

set(LOCALIZED_SOUND_SCRIPTS
    vo/aperture_ai/00_part1_entry-1.sox
    vo/aperture_ai/00_part1_entry-2.sox
    vo/aperture_ai/00_part1_entry-3.sox
    vo/aperture_ai/00_part1_entry-4.sox
    vo/aperture_ai/00_part1_entry-5.sox
    vo/aperture_ai/00_part1_entry-6.sox
    vo/aperture_ai/00_part1_entry-7.sox
    vo/aperture_ai/00_part1_success-1.sox
    vo/aperture_ai/00_part1_success-2.sox
    vo/aperture_ai/00_part1_success-3.sox
    vo/aperture_ai/00_part2_entry-1.sox
    vo/aperture_ai/00_part2_success-1.sox
    vo/aperture_ai/01_part1_entry-1.sox
    vo/aperture_ai/01_part1_entry-2.sox
    vo/aperture_ai/01_part1_get_portal_gun-1.sox
    vo/aperture_ai/01_part1_get_portal_gun-2.sox
    vo/aperture_ai/01_part1_get_portal_gun-3.sox
    vo/aperture_ai/01_part1_get_portal_gun-4.sox
    vo/aperture_ai/01_part1_get_portal_gun-5.sox
    vo/aperture_ai/01_part1_get_portal_gun-6.sox
    vo/aperture_ai/01_part1_get_portal_gun-7.sox
    vo/aperture_ai/01_part1_get_portal_gun-8.sox
    vo/aperture_ai/01_part2_entry-1.sox
    vo/aperture_ai/01_part2_success-1.sox
    vo/aperture_ai/02_part1_entry-1.sox
    vo/aperture_ai/02_part1_entry-2.sox
    vo/aperture_ai/02_part1_success-1.sox
    vo/aperture_ai/02_part1_success-2.sox
    vo/aperture_ai/02_part2_success-1.sox
    vo/aperture_ai/02_part2_success-2.sox
    vo/aperture_ai/03_part1_entry-1.sox
    vo/aperture_ai/03_part1_entry-2.sox
    vo/aperture_ai/03_part1_success-1.sox
    vo/aperture_ai/03_part2_entry-1.sox
    vo/aperture_ai/03_part2_platform_activated-1.sox
    vo/aperture_ai/04_part1_entry-1.sox
    vo/aperture_ai/04_part1_success-1.sox
    vo/aperture_ai/05_part1_entry-1.sox
    vo/aperture_ai/05_part1_entry-2.sox
    vo/aperture_ai/05_part1_nag1-1.sox
    vo/aperture_ai/05_part1_nag2-1.sox
    vo/aperture_ai/05_part1_nag3-1.sox
    vo/aperture_ai/05_part1_nag4-1.sox
    vo/aperture_ai/05_part1_nag5-1.sox
    vo/aperture_ai/05_part1_success-1.sox
    vo/aperture_ai/06_part1_entry-1.sox
    vo/aperture_ai/06_part1_success_1-1.sox
    vo/aperture_ai/06_part1_success_2-1.sox
    vo/aperture_ai/07_part1_entry-1.sox
    vo/aperture_ai/07_part1_entry-2.sox
    vo/aperture_ai/07_part1_entry-3.sox
    vo/aperture_ai/07_part1_get_device_component-1.sox
    vo/aperture_ai/07_part1_get_device_component-2.sox
    vo/aperture_ai/07_part1_get_device_component-3.sox
    vo/aperture_ai/07_part1_trapped-1.sox
    vo/aperture_ai/07_part1_trapped-2.sox
    vo/aperture_ai/07_part2_entry-1.sox
    vo/aperture_ai/07_part2_success-1.sox
    vo/aperture_ai/08_part1_entry-1.sox
    vo/aperture_ai/08_part1_entry-2.sox
    vo/aperture_ai/08_part1_entry-3.sox
    vo/aperture_ai/08_part1_success-1.sox
    vo/aperture_ai/08_part1_success-2.sox
    vo/aperture_ai/08_part1_trapped-1.sox
    vo/aperture_ai/08_part1_trapped-2.sox
    vo/aperture_ai/09_part1_entry-1.sox
    vo/aperture_ai/09_part1_entry-2.sox
    vo/aperture_ai/09_part1_success-1.sox
    vo/aperture_ai/10_part1_entry-1.sox
    vo/aperture_ai/10_part1_entry-2.sox
    vo/aperture_ai/10_part1_entry-3.sox
    vo/aperture_ai/10_part1_success-1.sox
    vo/aperture_ai/escape_01_part1_nag01-1.sox
    vo/aperture_ai/generic_crate_vaporized_in_emancipation_grid-1.sox
    vo/aperture_ai/generic_crate_vaporized_in_emancipation_grid-2.sox
    vo/aperture_ai/generic_security_camera_destroyed-1.sox
    vo/aperture_ai/generic_security_camera_destroyed-2.sox
    vo/aperture_ai/generic_security_camera_destroyed-3.sox
    vo/aperture_ai/generic_security_camera_destroyed-4.sox
    vo/aperture_ai/generic_security_camera_destroyed-5.sox
)

# TODO: rename to .sox after makefile is no longer in use
set(MUSIC_SCRIPTS
    music/portal_procedural_jiggle_bone.msox
    music/portal_self_esteem_fund.msox
    music/portal_still_alive.msox
    music/portal_subject_name_here.msox
    music/portal_taste_of_blood.msox
)

set(INSTRUMENT_BANKS
    ambient/atmosphere/ambience_base.ins
    ambient/machines/beam_platform_loop1.ins
    ambient/music/looping_radio_mix.ins
    doors/door_metal_medium_open1.ins
    vehicles/fast_windloop1.ins
    vehicles/tank_turret_loop1.ins
    weapons/physcannon/energy_sing_loop4.ins
)

# TODO: remove
function(_add_sound_transform_command_direct SOUND_NAME ARGS OUTPUT_LIST)
    set(INPUT_FILE "${PAK_SOUND_DIR}/${SOUND_NAME}.wav")
    string(REPLACE " " ";" ARGS ${ARGS})

    set(OUTPUT_FILE "${PROJECT_BINARY_DIR}/${RELATIVE_CURRENT_DIR}/${SOUND_NAME}.wav")

    cmake_path(
        GET OUTPUT_FILE PARENT_PATH
        OUTPUT_DIR
    )

    add_custom_command(
        DEPENDS
            extract_vpks ${INPUT_FILE}
        OUTPUT
            ${OUTPUT_FILE}
        COMMAND
            ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND
            ${Sox_EXECUTABLE} ${INPUT_FILE} ${ARGS} ${OUTPUT_FILE} -V1
        COMMENT
            "Transforming $<PATH:RELATIVE_PATH,${INPUT_FILE},${PROJECT_SOURCE_DIR}>"
        VERBATIM
    )

    list(APPEND ${OUTPUT_LIST} ${OUTPUT_FILE})
    return(PROPAGATE ${OUTPUT_LIST})
endfunction()

function(_add_sound_transform_command_sox SOUND_SCRIPT INPUT_FILE OUTPUT_FILE)
    cmake_path(
        GET OUTPUT_FILE PARENT_PATH
        OUTPUT_DIR
    )

    add_custom_command(
        DEPENDS
            extract_vpks ${INPUT_FILE}
            ${CONVERT_ASSET}
            ${SOUND_SCRIPT}
        OUTPUT
            ${OUTPUT_FILE}
        COMMAND
            ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND
            ${Python3_EXECUTABLE} ${CONVERT_ASSET}
            ${Sox_EXECUTABLE} ${INPUT_FILE} ${SOUND_SCRIPT} ${OUTPUT_FILE} -V1
        COMMENT
            "Transforming $<PATH:RELATIVE_PATH,${INPUT_FILE},${PROJECT_SOURCE_DIR}>"
        VERBATIM
    )
endfunction()

function(_add_sound_transform_command_jsox SOUND_SCRIPT INPUT_FILE OUTPUT_FILE)
    add_custom_command(
        DEPENDS
            extract_vpks ${INPUT_FILE}
            ${JSOX}
            ${SOUND_SCRIPT}
        OUTPUT
            ${OUTPUT_FILE}
        COMMAND
            ${NodeJs_EXECUTABLE} ${JSOX}
            ${Sox_EXECUTABLE} ${SOUND_SCRIPT} ${INPUT_FILE} ${OUTPUT_FILE}
        COMMENT
            "Transforming $<PATH:RELATIVE_PATH,${INPUT_FILE},${PROJECT_SOURCE_DIR}>"
        VERBATIM
    )
endfunction()

function(_add_sound_transform_command SOUND_SCRIPT INPUT_FILE OUTPUT_NAME OUTPUT_LIST)
    # TODO: change output to PAK_MODIFIED_SOUND_DIR once makefile is no longer in use
    #   Better place for it, and also allows .ins to not depend on hard-coded build path
    set(SOUND_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/${SOUND_SCRIPT}")
    set(OUTPUT_FILE "${PROJECT_BINARY_DIR}/${RELATIVE_CURRENT_DIR}/${OUTPUT_NAME}.wav")

    if (SOUND_SCRIPT MATCHES ".*\.jsox")
        _add_sound_transform_command_jsox(${SOUND_SCRIPT} ${INPUT_FILE} ${OUTPUT_FILE})
    else()
        _add_sound_transform_command_sox(${SOUND_SCRIPT} ${INPUT_FILE} ${OUTPUT_FILE})
    endif()

    list(APPEND ${OUTPUT_LIST} ${OUTPUT_FILE})
    return(PROPAGATE ${OUTPUT_LIST})
endfunction()

function(_add_music_transform_command MUSIC_SCRIPT OUTPUT_LIST)
    cmake_path(
        REMOVE_EXTENSION MUSIC_SCRIPT
        OUTPUT_VARIABLE MUSIC_NAME
    )

    # TODO: change output to PAK_MODIFIED_SOUND_DIR once makefile is no longer in use
    set(MUSIC_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/${MUSIC_SCRIPT}")
    set(INPUT_FILE "${PAK_SOUND_DIR}/${MUSIC_NAME}.mp3")
    set(CONVERTED_FILE "${PAK_SOUND_DIR}/${MUSIC_NAME}.wav")
    set(OUTPUT_FILE "${PROJECT_BINARY_DIR}/${RELATIVE_CURRENT_DIR}/${MUSIC_NAME}.wav")

    # First convert to WAV
    add_custom_command(
        DEPENDS
            extract_vpks ${INPUT_FILE}
        OUTPUT
            ${CONVERTED_FILE}
        COMMAND
            ${FFmpeg_EXECUTABLE}
            -i ${INPUT_FILE} -loglevel error -y ${CONVERTED_FILE}
        COMMENT
            "Converting $<PATH:RELATIVE_PATH,${INPUT_FILE},${PROJECT_SOURCE_DIR}>"
        VERBATIM
    )

    # Now we can process the WAV
    _add_sound_transform_command_sox(${MUSIC_SCRIPT} ${CONVERTED_FILE} ${OUTPUT_FILE})

    list(APPEND ${OUTPUT_LIST} ${OUTPUT_FILE})
    return(PROPAGATE ${OUTPUT_LIST})
endfunction()

# Add commands for transforming sound files
# Music is stored as MP3 and is converted to WAV first

set(SOUNDS_TRANSFORMED "")

# TODO: remove this special casing once makefile is no longer in use (just use .sox)
_add_sound_transform_command_direct(
    vehicles/tank_turret_loop1
    "-b 16"
    SOUNDS_TRANSFORMED
)
_add_sound_transform_command_direct(
    ambient/atmosphere/ambience_base
    "-c 1 -r 22050"
    SOUNDS_TRANSFORMED
)

foreach(SOUND_SCRIPT ${SOUND_SCRIPTS})
    cmake_path(
        REMOVE_EXTENSION SOUND_SCRIPT
        OUTPUT_VARIABLE SOUND_NAME
    )

    set(INPUT_FILE "${PAK_SOUND_DIR}/${SOUND_NAME}.wav")
    set(OUTPUT_FILE "${PROJECT_BINARY_DIR}/${RELATIVE_CURRENT_DIR}/${SOUND_NAME}.wav")
    _add_sound_transform_command(${SOUND_SCRIPT} ${INPUT_FILE} ${SOUND_NAME} SOUNDS_TRANSFORMED)
endforeach()

# Localized sounds
# Sounds within a language must be contiguous, so loop over languages first
foreach(LANGUAGE ${AUDIO_LANGUAGES_LIST})
    foreach(SOUND_SCRIPT ${LOCALIZED_SOUND_SCRIPTS})
        cmake_path(
            REMOVE_EXTENSION SOUND_SCRIPT
            OUTPUT_VARIABLE SOUND_NAME
        )

        _get_localized_pak_sound_dir(${LANGUAGE} INPUT_DIR)
        _get_localized_sound_name(${SOUND_NAME} ${LANGUAGE} LOCALIZED_NAME)
        set(INPUT_FILE "${INPUT_DIR}/${SOUND_NAME}.wav")

        _add_sound_transform_command(${SOUND_SCRIPT} ${INPUT_FILE} ${LOCALIZED_NAME} SOUNDS_TRANSFORMED)
    endforeach()
endforeach()

# Music
foreach(MUSIC_SCRIPT ${MUSIC_SCRIPTS})
    _add_music_transform_command(${MUSIC_SCRIPT} SOUNDS_TRANSFORMED)
endforeach()

######################
## Sound conversion ##
######################

function(_add_sound_convert_command INPUT_FILE OUTPUT_LIST)
    cmake_path(
        REPLACE_EXTENSION INPUT_FILE ".aifc"
        OUTPUT_VARIABLE OUTPUT_FILE
    )

    add_custom_command(
        DEPENDS
            ${INPUT_FILE}
        OUTPUT
            ${OUTPUT_FILE}
        COMMAND
            ${SFZ2N64_EXECUTABLE} -o ${OUTPUT_FILE} ${INPUT_FILE}
        COMMENT
            "Converting $<PATH:RELATIVE_PATH,${INPUT_FILE},${PROJECT_SOURCE_DIR}>"
        VERBATIM
    )

    list(APPEND ${OUTPUT_LIST} ${OUTPUT_FILE})
    return(PROPAGATE ${OUTPUT_LIST})
endfunction()

# Add commands for converting transformed sound files to N64 AIFC (compressed AIFF)

set(SOUNDS_CONVERTED "")

foreach(TRANSFORMED_SOUND ${SOUNDS_TRANSFORMED})
    _add_sound_convert_command(${TRANSFORMED_SOUND} SOUNDS_CONVERTED)
endforeach()

add_custom_target(sounds
    DEPENDS ${SOUNDS_CONVERTED}
)

############################
## Sound table generation ##
############################

set(SOUND_TABLE_DEPENDENCIES ${SOUNDS_CONVERTED})
set(SOUND_TABLE_INPUTS "")

foreach(INS_BANK ${INSTRUMENT_BANKS})
    cmake_path(
        REMOVE_EXTENSION INS_BANK
        OUTPUT_VARIABLE SOUND_NAME
    )

    # Each bank references a WAV. Keep track of the dependency.
    #
    # Some banks depend on converted sounds instead of unmodified.
    # That dependency is taken care of via SOUNDS_CONVERTED.
    list(APPEND SOUND_TABLE_DEPENDENCIES "${PAK_SOUND_DIR}/${SOUND_NAME}.wav")
    list(APPEND SOUND_TABLE_INPUTS "${CMAKE_CURRENT_SOURCE_DIR}/${INS_BANK}")
endforeach()

foreach(CONVERTED_SOUND ${SOUNDS_CONVERTED})
    cmake_path(
        RELATIVE_PATH CONVERTED_SOUND
        BASE_DIRECTORY "${PROJECT_BINARY_DIR}/${RELATIVE_CURRENT_DIR}"
        OUTPUT_VARIABLE INS_BANK
    )
    cmake_path(
        REPLACE_EXTENSION INS_BANK ".ins"
        OUTPUT_VARIABLE INS_BANK
    )

    # Only include the sound if an instrument bank doesn't already do so
    if (NOT INS_BANK IN_LIST INSTRUMENT_BANKS)
        list(APPEND SOUND_TABLE_INPUTS ${CONVERTED_SOUND})
    endif()
endforeach()

# Avoid extremely long argument list (MSYS2 has low ARG_MAX)
list(TRANSFORM SOUND_TABLE_INPUTS REPLACE "${PROJECT_SOURCE_DIR}/" "" OUTPUT_VARIABLE SOUND_TABLE_INPUTS)

# Add commands for generating sound tables

set(SOUND_TABLE_SOUNDS "${PROJECT_BINARY_DIR}/${RELATIVE_CURRENT_DIR}/sounds.sounds")
set(SOUND_TABLE_TBL "${PROJECT_BINARY_DIR}/${RELATIVE_CURRENT_DIR}/sounds.sounds.tbl")
set(SOUND_DATA_TABLE_FILES
    ${SOUND_TABLE_SOUNDS}
    ${SOUND_TABLE_TBL}
)
add_custom_command(
    DEPENDS
        extract_vpks sounds ${SOUND_TABLE_DEPENDENCIES}
    OUTPUT
        ${SOUND_DATA_TABLE_FILES}
    COMMAND
        ${SFZ2N64_EXECUTABLE} -o ${SOUND_TABLE_SOUNDS} ${SOUND_TABLE_INPUTS}
    WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}
    COMMENT
        "Generating sound data tables"
    VERBATIM
)

set(BUILD_AUDIO_DIR "${PROJECT_BINARY_DIR}/src/audio")
set(CLIPS_H "${BUILD_AUDIO_DIR}/clips.h")
set(LANGUAGES_H "${BUILD_AUDIO_DIR}/languages.h")
set(LANGUAGES_C "${BUILD_AUDIO_DIR}/languages.c")
set(SOUND_LOOKUP_TABLE_FILES
    ${CLIPS_H}
    ${LANGUAGES_H}
    ${LANGUAGES_C}
)
add_custom_command(
    DEPENDS
        extract_vpks sounds ${SOUND_TABLE_DEPENDENCIES}
        ${GEN_SOUND_IDS}
    OUTPUT
        ${SOUND_LOOKUP_TABLE_FILES}
    COMMAND
        ${NodeJs_EXECUTABLE} ${GEN_SOUND_IDS}
        --out-dir ${BUILD_AUDIO_DIR} ${SOUND_TABLE_INPUTS}
    WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}
    COMMENT
        "Generating sound lookup tables"
    VERBATIM
)

add_custom_target(sound_tables
    DEPENDS
        ${SOUND_DATA_TABLE_FILES}
        ${SOUND_LOOKUP_TABLE_FILES}
)

add_custom_target(sound_data_tables
    DEPENDS
        sound_tables
        ${SOUND_DATA_TABLE_FILES}
)
set_target_properties(sound_data_tables PROPERTIES
    OUTPUTS "${SOUND_DATA_TABLE_FILES}"
)

add_library(sound_lookup_tables INTERFACE)
add_dependencies(sound_lookup_tables sound_tables)
target_sources(sound_lookup_tables INTERFACE
    ${SOUND_LOOKUP_TABLE_FILES}
)
