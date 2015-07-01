.PHONY: clean All

All:
	@echo "----------Building project:[ model - Debug ]----------"
	@$(MAKE) -f  "model.mk"
	@echo "----------Building project:[ OrcaMento - Debug ]----------"
	@$(MAKE) -f  "OrcaMento.mk"
clean:
	@echo "----------Cleaning project:[ model - Debug ]----------"
	@$(MAKE) -f  "model.mk"  clean
	@echo "----------Cleaning project:[ OrcaMento - Debug ]----------"
	@$(MAKE) -f  "OrcaMento.mk" clean
