# (1)コンパイラ
CC  = g++
# (2)コンパイルオプション
CFLAGS    = 
# (3)実行ファイル名
TARGET  = main
# (4)コンパイル対象のソースコード
SRCS    = main.cpp
SRCS	+= glad.cpp
SRCS	+= src/GDK/Window.cpp
SRCS	+= src/GDK/Shader.cpp
SRCS	+= src/Renderer/Object.cpp
SRCS	+= src/Game.cpp
#SRCS	+= src/SEL/Structure.cpp

# (5)オブジェクトファイル名
OBJS    = $(notdir $(SRCS:.cpp=.o))

#	オブジェクトディレクトリ
OBJDIR = obj

# (6)インクルードファイルのあるディレクトリパス
INCDIR  = -Iinclude 
#	INCDIR 	+= -I -x C:\Users\rayrk\Downloads\Game\lib-mingw-w64\libglfw3.a
# (7)ライブラリファイルのあるディレクトリパス
LIBDIR  =	-Llib

# (8)追加するライブラリファイル
LIBS    = -lglfw3 -lgdi32 -lshell32 -lopengl32

# (9)ターゲットファイル生成
$(TARGET): $(OBJS)
		$(CC) $(INCDIR) -o $@ $(SRCS) $(LIBDIR) $(LIBS)

# (10)オブジェクトファイル生成
$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) $(INCDIR) -c $(SRCS)

# (11)"make all"で make cleanとmakeを同時に実施。
all: clean $(OBJS) $(TARGET)
# (12).oファイル、実行ファイル、.dファイルを削除
clean:
		-rm -f $(OBJS) $(TARGET) *.d

ex:
		./$(TARGET)