# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

OBJS += \
	$(LOCAL_DIR)/version.o \

# Generate the version tag from VCS
LK2ND_VERSION := $(shell lk2nd/scripts/describe-version.sh)
LK2ND_BUILD_TIME_IST := $(shell python3 -c "import datetime; print((datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(hours=5, minutes=30)).strftime('%Y-%m-%d %H:%M:%S IST'))")
VERSION_FILE := $(BUILDDIR)/$(LOCAL_DIR)/tag.c

.FORCE:

$(VERSION_FILE): .FORCE
	@$(MKDIR)
	@echo "const char* LK2ND_VERSION = \"$(LK2ND_VERSION)\";" > $@.tmp
	@echo "const char* LK2ND_BUILD_TIME_IST = \"$(LK2ND_BUILD_TIME_IST)\";" >> $@.tmp
	@if ! cmp -s $@.tmp $@; then				\
		echo generating $@ for lk2nd $(LK2ND_VERSION) \($(LK2ND_BUILD_TIME_IST)\);	\
		mv $@.tmp $@;					\
	fi

OBJS += \
	$(LOCAL_DIR)/tag.o \
