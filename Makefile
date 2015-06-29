.PHONY: clean All

All:
	@echo "----------Building project:[ model - Debug ]----------"
	@$(MAKE) -f  "model.mk"
	@echo "----------Building project:[ test - Debug ]----------"
	@$(MAKE) -f  "test.mk"
clean:
	@echo "----------Cleaning project:[ model - Debug ]----------"
	@$(MAKE) -f  "model.mk"  clean
	@echo "----------Cleaning project:[ test - Debug ]----------"
	@$(MAKE) -f  "test.mk" clean
