# StDownloader
C++ʵ�ֵĿ�ƽ̨ songtaste.com �������ع���

# ��������

QtCreator with MingGW 4.8 ��32bit��

# ʹ�õĿ�

* boost 1.56 ��δ��������Ŀ�ڣ�

* avhttp 2.9.9

* jsoncpp 0.7.0

* ffmpeg ���ṩ�����Ƴ���

# ����

����򵥽������׹�����`Windows`�Լ�`Linux`�µı��뷽����

����ǰ����߱�����������

* boost_1_56_0 ������

* cmake 2.8 ������

* ������ MinGW��Windows�� 4.8 �����ϣ�g++ 4.8��Linux��������

## ����boost

boost��ٷ���վ�ṩ�����°汾��boost���뷽����

### Windows

http://www.boost.org/doc/libs/1_57_0/more/getting_started/windows.html#prepare-to-use-a-boost-library-binary

### Unix��Linux��MacOS��

http://www.boost.org/doc/libs/1_57_0/more/getting_started/unix-variants.html#easy-build-and-install

## ����jsoncpp

### Windows

```
$ cd ./libs/jsoncpp-0.7.0/
$ cmake . -G "MinGW Makefiles"
$ mingw32-make
```

��ɺ���`lib`�¿����ҵ�`libjsoncpp.a`

### Linux

```

```

## ����StDownloader

��Ȼʹ��Qt��qmake�����п�������Ϊ�˼�㣬ʹ��`cmake`���п��ٹ�����

### Windows

������MinGWΪ�����ٶ�boost��Ŀ¼��`D:/libs/boost_1_56_0`����CMakeLists.txt��

����Ŀ��Ŀ¼ִ�У�

```
$ cmake . -G "MinGW Makefiles"
$ mingw32-make
```

����Ҳ���boost���ͷ�ļ������ڶ����`CMakeLists`���޸�`BOOST_ROOT`���á�

### Linux

```

```

# ���߼��

��Ҫ�ṩһ����ڣ�songtaste�����б�list�������أ�down����������parse�����ߡ�

## ����ڣ�songtaste��

��ڳ����ǵ��������������ߵ�;��֮һ��ִ������ʱ����Ҫ����ڴ����ӳ���������Ӧ�������ɡ�

## �б�list��

Ŀǰ�б���֧�֡�����Ƽ����������ַ��ࡱ����һ�����С�������б�������б�֧�ַ�ҳ��

Ϊ����֮�󿪷���GUI����Ľ��������н������json��ʽ����������б��֧�ֻ��档

### ʹ��ʾ��

**�鿴����**

```
$ songtaste list
or
$ songtaste list --help
```

**����Ƽ�**

```
$ songtaste list --recommend
#��ҳ
$ songtaste list --recommend --page 3
```

**�����б�**

```
$ songtaste list --category
```

**�����е������б�**

```
$ songtaste list --catsong --catid 2
$ songtaste list --catsong --catid 2 --page 2
```

**���б�**

```
$ songtaste list --week
```

**������Ѹ���**

```
$ songtaste list --weekchart
```

��Ҫ���湦�ܿ����� **config.json** �����û���·����Ȼ���������� **--cache** ѡ�

## ���أ�down��

���س������ʵʱ��ʾ���ؽ��Ⱥ������ٶȣ��������ļ���С�ȱ�Ҫ��Ϣ��

### ʹ��ʾ��

**�鿴����**

```
$ songtaste down
```

**����ָ��id������**

```
$ songtaste down --id 3468640
```

**��ȡָ��id��������Ϣ**

```
$ songtaste down --id 3468640 --info
```

**���ص�ָ��Ŀ¼**

```
$ songtaste down --id 3468640 --dir ./
```

**���ص�ָ��Ŀ¼��������** ��ԭʼ�������ǷǷ����ļ�����

```
$ songtaste down --id 3468640 --dir ./music --name my_music
```

## ������parse��

ͨ��ffmpeg�������ֿ��Եõ�ԭʼ�ĸ������ߵ���Ϣ��

### ʹ��ʾ��

**�鿴����**

```
$ songtaste parse
```

**����ָ������** ������ӵ���ffmpeg��

```
$ songtaste parse test.mp3
```

# ��������

��������ȡ�õ���Դ�����Ի�����������ѧϰ������

����ʹ�ù������ַ���ԭ���ֵİ�Ȩ��������ɾ����δ��ԭ��Ȩ������ɣ��κ��˲����������ã���������24Сʱ��ɾ����Ϊ�������߰�Ȩ���빺��ԭ����Ʒ��
