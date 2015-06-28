.PHONY: clean All

All:
	@echo "----------Building project:[ OrcaMento - Release ]----------"
	@$(MAKE) -f  "OrcaMento.mk"
clean:
	@echo "----------Cleaning project:[ OrcaMento - Release ]----------"
	@$(MAKE) -f  "OrcaMento.mk" clean
