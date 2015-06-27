.PHONY: clean All

All:
	@echo "----------Building project:[ OrcaMento - Debug ]----------"
	@$(MAKE) -f  "OrcaMento.mk"
clean:
	@echo "----------Cleaning project:[ OrcaMento - Debug ]----------"
	@$(MAKE) -f  "OrcaMento.mk" clean
