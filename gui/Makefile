#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(PSL1GHT)),)
$(error \"Please set PSL1GHT in your environment. export PSL1GHT=<path>\")
endif

TC_ADD		:=	`date +%d%H%M`
ICON0		:=	$(CURDIR)/ICON0.PNG
SFOXML		:=	$(CURDIR)/sfo.xml

SCETOOL_FLAGS	?=	--self-app-version=0001000000000000  --sce-type=SELF --compress-data=TRUE --self-add-shdrs=TRUE --skip-sections=FALSE --key-revision=1 \
					--self-auth-id=1010000001000003 --self-vendor-id=01000002 --self-fw-version=0003004000000000 \
					--self-ctrl-flags 4000000000000000000000000000000000000000000000000000000000000002 \
					--self-cap-flags 00000000000000000000000000000000000000000000007B0000000100000000

include $(PSL1GHT)/ppu_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	source
DATA		:=	data
INCLUDES	:=	include
PKGFILES 	:=	$(CURDIR)/pkgdata

APP_VER		:=	01.00
VERSIONSTR	:=	1.0.0-alpha
TITLE		:=	Artemis PS3 Lite ($(VERSIONSTR))
APPID		:=	ARTP30002
CONTENTID	:=	UP0001-$(APPID)_00-0000000000000000


#---------------------------------------------------------------------------------
# sfo contents generated with the supplied variables above
#---------------------------------------------------------------------------------
define SFOCONTENTS
<?xml version="1.0" ?>\n<sfo>\n	<value name="APP_VER" type="string"> \n		$(APP_VER) \n	</value>\n	<value name="ATTRIBUTE" type="integer">\n		133\n	</value>\n	<value name="BOOTABLE" type="integer">\n		1\n	</value>\n	<value name="CATEGORY" type="string">\n		HG\n	</value>\n	<value name="LICENSE" type="string">\n		This application was created with the official non-official SDK called PSL1GHT, for more information visit http://www.psl1ght.com/ . This is in no way associated with Sony Computer Entertainment Inc., please do not contact them for help, they will not be able to provide it.\n	</value>\n	<value name="PARENTAL_LEVEL" type="integer">\n		0\n	</value>\n	<value name="PS3_SYSTEM_VER" type="string">\n		03.4000\n	</value>\n	<value name="RESOLUTION" type="integer">\n		63\n	</value>\n	<value name="SOUND_FORMAT" type="integer">\n		279\n	</value>\n	<value name="TITLE" type="string">\n		$(TITLE)\n	</value>\n	<value name="TITLE_ID" type="string">\n		$(APPID)\n	</value>\n	<value name="VERSION" type="string">\n		01.00\n	</value>\n</sfo>
endef

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

CFLAGS		=	-O3 -Wall -mcpu=cell -DARTEMIS_VERSION=\"$(VERSIONSTR)\" -DARTEMIS_PATH=\"//dev_hdd0/game/$(APPID)/USRDIR/\" $(MACHDEP) $(INCLUDE)
CXXFLAGS	=	$(CFLAGS)

LDFLAGS		=	$(MACHDEP) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=	-lMini2D -lspu_sound -ltiny3d -lfreetype -lconfig -lgcm_sys -lrsx -lsysutil -lio -lnet -lz -laudioplayer -laudio -lmpg123 -logg -lsysmodule -lm \
			-lpngdec -ljpgdec

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

export BUILDDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
PNGFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.png)))
JPGFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.jpg)))
TTFFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.ttf)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES	:=	$(addsuffix .o,$(PNGFILES)) \
					$(addsuffix .o,$(JPGFILES)) \
					$(addsuffix .o,$(BINFILES)) \
					$(addsuffix .o,$(TTFFILES)) \
					$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) \
					$(sFILES:.s=.o) $(SFILES:.S=.o)
	
#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES), -I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					$(LIBPSL1GHT_INC) \
					-I$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
					$(LIBPSL1GHT_LIB)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@echo -e '$(SFOCONTENTS)' > $(SFOXML)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@rm -fr $(BUILD) $(OUTPUT).elf
	@rm -fr $(OUTPUT).self $(OUTPUT).fake.self
	@rm -fr $(OUTPUT).pkg $(OUTPUT).gnpdrm.pkg

#---------------------------------------------------------------------------------
run: $(BUILD)
	ps3load $(OUTPUT).self

#---------------------------------------------------------------------------------
rpcs3: $(BUILD)
	$(RPCS3) $(OUTPUT).self

#---------------------------------------------------------------------------------
all: $(BUILD) pkg

#---------------------------------------------------------------------------------
pkg: $(BUILD) $(OUTPUT).pkg

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).self: $(OUTPUT).elf
$(OUTPUT).elf:	$(OFILES)

#---------------------------------------------------------------------------------
# This rule links in binary data with the .bin extension
#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo '[BIN2O]  $(notdir $<)'
	@$(bin2o)
#---------------------------------------------------------------------------------
%.jpg.o	:	%.jpg
#---------------------------------------------------------------------------------
	@echo '[BIN2O]  $(notdir $<)'
	@$(bin2o)
#---------------------------------------------------------------------------------
%.png.o	:	%.png
#---------------------------------------------------------------------------------
	@echo '[BIN2O]  $(notdir $<)'
	@$(bin2o)
#---------------------------------------------------------------------------------
%.ttf.o	:	%.ttf
#---------------------------------------------------------------------------------
	@echo '[BIN2O]  $(notdir $<)'
	@$(bin2o)
#---------------------------------------------------------------------------------
%.o:		%.cpp
#---------------------------------------------------------------------------------
	@echo '[CC]  $(notdir $<)'
	@$(CC) $(DEPSOPTIONS) $(CFLAGS) -c $< -o $@



-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
