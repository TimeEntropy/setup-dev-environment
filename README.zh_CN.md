# 我是如何配置我的开发环境的？

> **提示: 由于我只在Windows平台上工作，因此该文档应该只对Windows用户有所帮助**

## 1. 我所使用的软件

- VSCode
- CMake
- llvm-mingw
- git
- vcpkg

## 2. 下载并配置所有东西……

> **提示: '${_}'字符串出现的地方应替换成对应含义的字符串**

### git

#### 安装

在[这里](https://git-scm.com/downloads)找到安装包

在Windows平台上，你通常会下载到源自[git-for-windows](https://github.com/git-for-windows/git/releases)的安装包<br>
因为git需要在类Unix环境下运行

#### 环境变量

- 新建
  |     键     |          值           | 含义          |
  | :--------: | :-------------------: | :------------ |
  | `GIT_ROOT` | `${git-install-path}` | git的安装路径 |

- 在`PATH`中添加：
  |        值        | 用途                                        |
  | :--------------: | :------------------------------------------ |
  |   `%GIT_ROOT%`   | 让`bash`脚本可以识别到执行依赖              |
  | `%GIT_ROOT%/bin` | 在本地命令提示符中可以使用`bash`和`git`指令 |

#### 配置git

1. 打开`bash`或者其它系统原生控制台，例如`cmd`或`PowerShell`
2. 执行以下命令:
   ```shell
   git config --global user.name ${your-name}
   git config --global user.email ${your-email}
   git config --global init.defaultBranch main

   # 使用VSCode编辑一切!
   git config --global core.editor 'code --wait'
   git config --global diff.tool vscode
   git config --global merge.tool vscode
   git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'
   git config --global mergetool.vscode.cmd 'code --wait $MERGED'

   # 如果你在做git操作时网络不好，可以尝试这些配置命令：
   git config --global http.sslbackend openssl
   git config --global http.sslVerify false
   git config --global https.sslbackend openssl
   git config --global https.sslVerify false
   git config --global receive.keepAlive true
   ```
   或者你可以编辑文件`%USERPROFILE%/.gitconfig`，<br>
   拷贝以下内容覆盖进配置文件中（别忘了替换掉${_}字符串**）：
	```ini
	[core]
		autocrlf = true
		editor   = code
	[user]
		name  = ${your-name}
		email = ${your-email}
	[init]
		defaultBranch = main

	[diff]
		tool = vscode
	[difftool "vscode"]
		cmd = code --wait --diff $LOCAL $REMOTE
	[merge]
		tool = vscode
	[mergetool "vscode"]
		cmd = code --wait $MERGED

	[http]
		sslbackend = openssl
		sslVerify  = false
	[https]
		sslbackend = openssl
		sslVerify  = false
	[receive]
		keepAlive = true
	```
   > **提示: 你可以使用`git config --help`命令找到所有的配置变量，
     就在`Variables`小节里**

### CMake

#### 安装

在[这里](https://cmake.org/download/)找到安装包

遵循安装器的引导即可完成安装

#### 环境变量

- 新建
  |      键      |           值            | 含义            |
  | :----------: | :---------------------: | :-------------- |
  | `CMAKE_ROOT` | `${cmake-install-path}` | cmake的安装路径 |

- 在`PATH`中添加：
  |         值         | 用途                                  |
  | :----------------: | :------------------------------------ |
  | `%CMAKE_ROOT%/bin` | 在本地命令提示符中可以使用`cmake`指令 |

### llvm-mingw

#### 安装

在[这里](https://github.com/mstorsjo/llvm-mingw/releases)找到安装包

高度建议下载使用LLVM18构建的包，例如：https://github.com/mstorsjo/llvm-mingw/releases/tag/20240619

因为在LLVM19中，`stdc++`将不再支持 **`std::char_traits<unsigned int>`的默认模板特化**，
但直到今天(2024/12/14)，一些库（例如[sfml](https://github.com/SFML/SFML)、
[efsw](https://github.com/SpartanJ/efsw)等）还在使用这个模板特化，因此当你在使用这些库参与构建时就会遇到“**模板实例找不到**”的异常！

细节参考：https://libcxx.llvm.org/ReleaseNotes/19.html#deprecations-and-removals

#### 环境变量

- 新建
  |        键         |              值              | 含义                 |
  | :---------------: | :--------------------------: | :------------------- |
  | `LLVM_MINGW_ROOT` | `${llvm-mingw-install-path}` | llvm-mingw的安装路径 |

- 在`PATH`中添加：
  |           值            | 用途                                                                                |
  | :---------------------: | :---------------------------------------------------------------------------------- |
  | `%LLVM_MINGW_ROOT%/bin` | 在本地命令提示符中可以使用llvm-mingw提供的工具集，<br>如`clang`、`clangd`、`lldb`等 |

### VSCode

#### 安装

在[这里](https://code.visualstudio.com/Download)找到安装包

运行安装器或者解压压缩包到你的环境中

#### 环境变量

- 新建
  |      键       |            值            | 含义             |
  | :-----------: | :----------------------: | :--------------- |
  | `VSCODE_ROOT` | `${vscode-install-path}` | VSCode的安装路径 |

- 在`PATH`中添加：
  |         值          | 用途                                               |
  | :-----------------: | :------------------------------------------------- |
  | `%VSCODE_ROOT%/bin` | 在本地命令提示符中可以使用`code`指令直接打开VSCode |

#### 为VSCode安装插件

1. 打开VSCode编辑器，键盘`Ctrl+Shift+X`打开插件商店
2. 如果你需要定制编辑器UI的语言，在搜索栏搜索你的语言并下载看到的第一个插件即可
3. 安装需要的开发插件，由于我想要做C++开发所以我会下载以下插件：
   - **clangd**     : llvm-vs-code-extensions.vscode-clangd
   - **CMake**      : twxs.cmake
   - **CMake Tools**: ms-vscode.cmake-tools
   - **CodeLLDB**   : vadimcn.vscode-lldb
   > 提示: 复制扩展ID到搜索栏中可以直接找到扩展

### vcpkg

#### 安装

可以从[这里](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell#1---set-up-vcpkg)开始

1. 进入你的程序安装目录，例如`C:/dev/programs`
1. 在该目录启动`bash`或其它命令提示符
2. 执行：
   ```shell
   git clone https://github.com/microsoft/vcpkg.git
   ```
3. clone完成后执行：
   ```shell
   cd vcpkg; ./bootstrap-vcpkg.bat
   ```
   等待vcpkg安装完成

#### 环境变量

|              键              |           值            | 含义                                                      |
| :--------------------------: | :---------------------: | :-------------------------------------------------------- |
|         `VCPKG_ROOT`         | `${vcpkg-install-path}` | vcpkg的安装路径                                           |
| `VCPKG_DEFAULT_HOST_TRIPLET` |   `x64-mingw-static`    | vcpkg的主机默认三元组                                     |
|   `VCPKG_DEFAULT_TRIPLET`    |   `x64-mingw-static`    | vcpkg的目标默认三元组，在安装库时也将使用该变量构建目标库 |

## 3. 编写C++程序的示例

1. 创建你的项目根目录，例如`C:/dev/projects/test`，`test`是你的项目名称
2. 使用VSCode打开`test`文件夹
3. 在VSCode中创建终端，打开`bash`或者其它终端配置
4. 初始化git本地仓库：
   ```shell
   git init
   ```
5. 使用vcpkg安装包:
   ```shell
   vcpkg install SDL2
   ```
6. 创建文件夹构建树结构例如：
   ```
   .vscode/
     |-- launch.json
   test
     |-- src/
     |     |-- main.cpp
     |-- .gitignore
     |-- CMakeLists.txt
     |-- README.md
   ```
7. `CMakeLists.txt`：
```CMake
cmake_minimum_required(VERSION 3.20.0)

# vcpkg configs
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
if(NOT DEFINED VCPKG_TARGET_TRIPLET)
	set(VCPKG_TARGET_TRIPLET x64-mingw-static)
endif()

# variables
set(TEST_PROJECT_NAME test)
set(SDL2_LIBS
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>, SDL2::SDL2, SDL2::SDL2-static>
)

# files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# top project declare
project(${TEST_PROJECT_NAME} CXX)

# packages
find_package(SDL2 CONFIG REQUIRED)

# targets
add_executable(${TEST_PROJECT_NAME} ${SRC_FILES})
target_include_directories(${TEST_PROJECT_NAME} SYSTEM BEFORE
	PRIVATE ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(${TEST_PROJECT_NAME} PRIVATE
	${SDL2_LIBS}
)
```

8. 重启VSCode并打开`test`文件夹，
   通常VSCode的CMake插件会自动检测项目目录下的`CMakeLists.txt`，
   并自动完成一次配置，在VSCode的侧边栏也会出现CMake的工具按钮；
   <br>
   点击工具按钮，并点击`项目大纲 > 配置所有项目`，或者你可以在终端中手动配置：
   ```shell
   # run in bash
   cmake -Bbuild -DCMAKE_CXX_COMPILER=$LLVM_MINGW_ROOT/bin/clang++ -DVCPKG_TARGET_TRIPLET=x64-mingw-static -G"MinGW Makefiles"
   ```

9. `src/main.cpp`:
```c++
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
	SDL_Window*   window   = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool          running  = true;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		800,
		SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { running = false; break; }
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		{
			// DrawCalls
		}
		SDL_RenderPresent(renderer);
	}

	// CleanUp SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
```

10. `.vscode/launch.json`:
```json
{
	"configurations": [
		{
			"type": "lldb",
			"request": "launch",
			"name": "Debug",
			"program": "${workspaceFolder}/build/${workspaceFolderBasename}",
			"args": [],
			"cwd": "${workspaceFolder}",
			"preLaunchTask": "CMake: 生成",
		}
	]
}
```
之后你可以在VSCode使用`F5`调试你的程序

11. `.gitignore`:
```ini
##### dirs #####

# generated by clangd
.cache/

# only for vscode configs
.vscode/

# generated by CMake
build/
```

12. 完成git提交结束示例：
```shell
git status
git add *
git commit -m "job done"
```
