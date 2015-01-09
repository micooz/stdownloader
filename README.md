# StDownloader
C++实现的跨平台 songtaste.com 音乐下载工具

# 开发环境

QtCreator with MingGW 4.8 （32bit）

# 使用的库

* boost 1.56 （未包含在项目内）

* avhttp 2.9.9

* jsoncpp 0.7.0

* ffmpeg （提供二进制程序）

# 编译

下面简单介绍这套工具在`Windows`以及`Linux`下的编译方法。

编译前必须具备下列条件：

* boost_1_56_0 及以上

* cmake 2.8 及以上

* 编译器 MinGW（Windows） 4.8 及以上；g++ 4.8（Linux）及以上

## 编译boost

boost库官方网站提供了最新版本的boost编译方法：

### Windows

http://www.boost.org/doc/libs/1_57_0/more/getting_started/windows.html#prepare-to-use-a-boost-library-binary

### Unix（Linux，MacOS）

http://www.boost.org/doc/libs/1_57_0/more/getting_started/unix-variants.html#easy-build-and-install

## 编译jsoncpp

### Windows

```
$ cd ./libs/jsoncpp-0.7.0/
$ cmake . -G "MinGW Makefiles"
$ mingw32-make
```

完成后在`lib`下可以找到`libjsoncpp.a`

### Linux

```

```

## 编译StDownloader

虽然使用Qt（qmake）进行开发，但为了简便，使用`cmake`进行快速构建。

### Windows

下面以MinGW为例，假定boost根目录在`D:/libs/boost_1_56_0`（见CMakeLists.txt）

在项目根目录执行：

```
$ cmake . -G "MinGW Makefiles"
$ mingw32-make
```

如果找不到boost相关头文件，请在顶层的`CMakeLists`中修改`BOOST_ROOT`设置。

### Linux

```

```

# 工具简介

主要提供一主入口（songtaste）、列表（list）、下载（down）、解析（parse）工具。

## 主入口（songtaste）

入口程序是调用其他附属工具的途径之一，执行命令时仅需要给入口传递子程序名和相应参数即可。

## 列表（list）

目前列表功能支持“大家推荐”、“音乐分类”、“一周排行”的相关列表和音乐列表，支持分页。

为方便之后开发的GUI程序的解析，所有结果均以json格式输出。所有列表均支持缓存。

### 使用示例

**查看帮助**

```
$ songtaste list
or
$ songtaste list --help
```

**大家推荐**

```
$ songtaste list --recommend
#分页
$ songtaste list --recommend --page 3
```

**分类列表**

```
$ songtaste list --category
```

**分类中的音乐列表**

```
$ songtaste list --catsong --catid 2
$ songtaste list --catsong --catid 2 --page 2
```

**周列表**

```
$ songtaste list --week
```

**本周最佳歌曲**

```
$ songtaste list --weekchart
```

需要缓存功能可以在 **config.json** 中配置缓存路径，然后给命令添加 **--cache** 选项。

## 下载（down）

下载程序可以实时显示下载进度和下载速度，并给出文件大小等必要信息。

### 使用示例

**查看帮助**

```
$ songtaste down
```

**下载指定id的音乐**

```
$ songtaste down --id 3468640
```

**获取指定id的音乐信息**

```
$ songtaste down --id 3468640 --info
```

**下载到指定目录**

```
$ songtaste down --id 3468640 --dir ./
```

**下载到指定目录并重命名** （原始名可能是非法的文件名）

```
$ songtaste down --id 3468640 --dir ./music --name my_music
```

## 解析（parse）

通过ffmpeg解析音乐可以得到原始的歌名作者等信息。

### 使用示例

**查看帮助**

```
$ songtaste parse
```

**解析指定音乐** （将间接调用ffmpeg）

```
$ songtaste parse test.mp3
```

# 免责声明

本工具所取得的资源均来自互联网，仅供学习交流。

如在使用过程中侵犯了原音乐的版权，请予以删除，未经原版权作者许可，任何人不得擅作它用！请在下载24小时内删除！为尊重作者版权，请购买原版作品。
