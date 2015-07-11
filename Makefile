.PHONY: clean All

All:
	@echo "----------Building project:[ model - Release ]----------"
	@$(MAKE) -f  "model.mk"
	@echo "----------Building project:[ OrcaMento - Release ]----------"
	@$(MAKE) -f  "OrcaMento.mk"
clean:
	@echo "----------Cleaning project:[ model - Release ]----------"
	@$(MAKE) -f  "model.mk"  clean
	@echo "----------Cleaning project:[ OrcaMento - Release ]----------"
	@$(MAKE) -f  "OrcaMento.mk" clean
