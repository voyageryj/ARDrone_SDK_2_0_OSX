GEN_CUSTOM_HEADER:=../Common/generated_custom.h

include custom.makefile 
include config.makefile

GNUTOOLS_PATH=/usr/local/$(GNUTOOLS_VERSION)/bin

define ADD_RULE_TEMPLATE
  TO_BUILD+=build_$(1)
endef

# Add rule for each target
$(foreach target,$(TARGETS),$(eval $(call ADD_RULE_TEMPLATE,$(target))))
   
.PHONY: linux_sample svn_update $(TO_BUILD) build_libs $(MAKECMDGOALS)

all: $(GEN_CUSTOM_HEADER) build_libs $(TO_BUILD)

$(GEN_CUSTOM_HEADER): custom.makefile
	@echo "#ifndef _GENERATED_CUSTOM_CONFIGURATION_H_" > $@
	@echo "#define _GENERATED_CUSTOM_CONFIGURATION_H_" >> $@
	@echo >> $@
	@echo "#if  defined(BR2_PACKAGE_BCM4318_AP)" >> $@
	@echo "#  define AP" >> $@
	@echo "#else" >> $@
	@echo "#  define STA" >> $@
	@echo "#endif" >> $@
	@echo "#define CURRENT_NUM_VERSION_SOFT \"$(MAJOR_VERSION).$(MINOR_VERSION).$(MODIF_VERSION)\"" >> $@
	@echo "#define CURRENT_BUILD_DATE \"$(shell date +%F\ %H:%M)\"" >> $@
	@echo >> $@
ifeq ("$(VIDEO_YUV)","yes")
	@echo "#define USE_VIDEO_YUV" >> $@
endif
ifeq ("$(RECORD_VISION_DATA)","yes")
	@echo "#define RECORD_VISION_DATA" >> $@
endif
	@echo >> $@
	@echo "#define WIFI_NETWORK_NAME \"$(WIFI_NETWORK_NAME)\"" >> $@
	@echo "#define WIFI_BROADCAST \"$(WIFI_BROADCAST)\"" >> $@
	@echo "#define WIFI_ARDRONE_IP \"$(WIFI_ARDRONE_IP)\"" >> $@
	@echo >> $@
	@echo "#if defined(__linux__) || defined(USE_MINGW32)" >> $@
	@echo "# define WIFI_MOBILE_IP \"$(WIFI_MOBILE_IP)\"" >> $@
	@echo "# define WIRED_ITFNAME \"$(WIRED_ITFNAME)\"" >> $@
	@echo "#endif // ! __linux__" >> $@
	@echo >> $@
	@echo >> $@
	@echo "#endif // ! _GENERATED_CUSTOM_CONFIGURATION_H_" >> $@

ifneq "$(MAKECMDGOALS)" ""
  ifneq "$(MAKECMDGOALS)" "clean"
    ifneq "$(MAKECMDGOALS)" "update"
      $(MAKECMDGOALS):
      @echo -e "\nCannot make what you ask me to do :-("
    else
      $(MAKECMDGOALS): svn_update
    endif
  endif
endif

$(MAKECMDGOALS): build_libs $(TO_BUILD)

checkpackages:
ifeq ($(IPHONE_MODE),yes)
	sh $(shell pwd)/check_dependencies.sh iphone RELEASE_BUILD=$(RELEASE_BUILD) $(MAKECMDGOALS)
else
ifeq ($(USE_LINUX),yes)
	sh $(shell pwd)/check_dependencies.sh static RELEASE_BUILD=$(RELEASE_BUILD) $(MAKECMDGOALS)
else
ifeq ($(USE_OSX),yes)
	#basically this just builds FFMPEG as a static library, for OSX we assume you have it installed and the libraries are dynamically linkable,
	#relevant linking paths are added in common.makefile if the FFMPEG_EXTERN is turned on (which it is when USE_OSX is specified)
	#sh $(shell pwd)/check_dependencies.sh static RELEASE_BUILD=$(RELEASE_BUILD) $(MAKECMDGOALS)
else
ifeq ($(USE_ANDROID),yes)
    sh $(shell pwd)/check_dependencies.sh android_no_neon RELEASE_BUILD=$(RELEASE_BUILD) $(MAKECMDGOALS)
endif
endif
endif
endif

define GENERIC_RULES_TEMPLATE
build_$(1): 
	@$(MAKE) -C $(1) $(MAKECMDGOALS)
endef

$(foreach target,$(TARGETS),$(eval $(call GENERIC_RULES_TEMPLATE,$(target))))

build_libs: checkpackages
	@$(MAKE) PC_TARGET=yes USE_ARDRONE_TOOL=yes TARGET=pc_ USE_MINGW32=no -C ../Lib/Build $(MAKECMDGOALS)
	@$(MAKE) PC_TARGET=yes USE_ARDRONE_TOOL=no TARGET=pc_ USE_MINGW32=no -C ../Lib/Build $(MAKECMDGOALS)

ifeq ("$(MINGW32_MODE)","yes")
ifeq ($(shell which i586-mingw32msvc-gcc 2> /dev/null),)
        $(warning You need MinGW32 to compile My Ardrone lib for Windows if you want. (under Debian: apt-get install mingw32))
else
#	@$(MAKE) PC_TARGET=yes TARGET=mingw32_ USE_MINGW32=yes TMP_SDK_FLAGS="USE_MINGW32=yes NO_COM=yes USE_BLUEZ=no" -C ../Lib/Build $(MAKECMDGOALS)
#	@$(MAKE) PC_TARGET=yes TARGET=emb_mingw32_ USE_MINGW32=yes CONTROL_DLL=yes TMP_SDK_FLAGS="USE_MINGW32=yes NO_COM=yes USE_BLUEZ=no" -C ../Lib/Build $(MAKECMDGOALS)
endif
endif
ifeq ($(WIIMOTE_SUPPORT),yes)
#	@$(MAKE) PC_TARGET=yes TARGET=pc_ TMP_SDK_FLAGS="USE_BLUEZ=yes" -C ../Lib/libcwiid $(MAKECMDGOALS)
endif

define svn_update_template
   cd ../.. ; \
	echo "Checking out tag $(1) of $(2) ..." ; \
	if [ $(1) != head ] ; then \
	   svn co -r $(1) https://svn.ardrone.org/repo/ARDrone_API/$(2) ; \
	else \
		svn co https://svn.ardrone.org/repo/ARDrone_API/$(2) ; \
	fi ; \
	cd Soft/Build ; 
endef
	
svn_update:
	@-$(call svn_update_template,$(SDK_VERSION),ARDroneLib)
