deps_config := \
	/root/.local/ecos-sdk/tools/kconfig/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
