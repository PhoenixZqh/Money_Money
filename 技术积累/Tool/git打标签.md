# 一 打标签方法

1. 通过VScode自带git管理工具打标签，打完标签后再写上注释
2. 命令行打标签

   ```xml
   git tag v1.0     //这种只针对最新的提交

   ```

   ```xml
   git log --pretty=oneline --abbrev-commit
   git  tag v1.0 471fd27      //找到历史提交，然后打标签
   ```

   ```xml
   git tag -a v0.1 -m "version 0.1 released push url" d5a65e9        //边打标签边注释
   ```

# 二 查看标签

```
git show v1.0
```

```
git tag   //查看所有的标签
```

```
git push origin --tags    //上传所有的标签
```

# 三 删除标签

```xml
git tag -d <tag-name>  #删除本地标签
```

```xml
git push origin :refs/tags/<tag-name>   #删除标签
```
