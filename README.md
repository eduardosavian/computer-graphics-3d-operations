# cg-test


##

 g++ -o main src/main.cpp -lGL -lGLU -lglut

 sudo yum install freeglut-devel

 sudo dnf remove freeglut-3.4.0-4.fc39.x86_64

 .PHONY: clean

clean:
    rm -f $(OBJS) $(BUILD_DIR)/$(TARGET)
