## part 1
```bash
➜  Django git:(master) ✗ django-admin startproject mysite
➜  mysite git:(master) ✗ tree 
.
├── manage.py
└── mysite
    ├── __init__.py     一个空文件告诉python这个目录应该被认为是一个Python包
    ├── settings.py     Django项目配置文件
    ├── urls.py         Django项目URL声明
    └── wsgi.py         作为项目运行在WSGI兼容的Web服务器上的入口
 ➜  mysite git:(master) ✗ python manage.py runserver
```

### 创建投票应用
##### 项目VS应用
应用是一个专门做某件事的网络应用程序——比如博客系统，或者公共记录的数据库，或者简单的投票程序。
项目则是一个网站使用的配置和应用的集合。项目可以包含很多个应用。应用可以被很多个项目使用。
```bash
➜  mysite git:(master) ✗ python manage.py startapp polls
➜  polls git:(master) ✗ tree
.
├── admin.py
├── apps.py
├── __init__.py
├── migrations
│   └── __init__.py
├── models.py
├── tests.py
└── views.py

1 directory, 7 files
```
##### 编写第一个视图
* polls/views.py
* 为了创建URLconfs,在polls目录里创建一个urls.py
```python
from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
]
```
* 下一步是要在根URLconf文件中指定创建的polls.urls模块,在mysite/urls.py文件的urlpatterns列表里插入一个include(),如下
```python
from django.contrib import admin
from django.urls import include, path

urlpatterns = [
    path(route='polls/', view=include('polls.urls')),
    path('admin/', admin.site.urls),
]
```
函数include()允许引用其他URLconfs.

##### path()
path()具有四个参数,两个必选参数:route和view,两个可选参数kwargs和name
* route:
route是一个匹配URL的准则(类似正则表达式).当Django响应一个请求时它会从urlpatterns的
第一项开始,按顺序依次匹配列表中的项,直到找到匹配的项
* view:
当Django找到了匹配的准则,就会调用这个特定的视图参数,并传入一个HTTPRequest对象作为第一个参数,
被"捕获"的参数以关键字的形式传入
* kwargs:
任意个关键字参数可以作为一个字典传递给目标视图函数
* name:
为URL取名使得在Django的任意地方唯一地引用它,尤其是在模板中

## part 2
#### 数据库配置
打开mysite/settings.py.这是包含了Django项目设置的Python模块
通常这个配置文件使用SQLite作为默认浏览器.
* ENGINE -- 可选值有 'django.db.backends.sqlite3'， 'django.db.backends.postgresql'，'django.db.backends.mysql'， 'django.db.backends.oracle'。
* NAME - 数据库的名称。
* 如果使用的是 SQLite，数据库将是你电脑上的一个文件，在这种情况下， NAME 应该是此文件的绝对路径，包括文件名。**默认值 os.path.join(BASE_DIR, 'db.sqlite3') 将会把数据库文件储存在项目的根目录**
通常， INSTALLED_APPS 默认包括了以下 Django 的自带应用：

* django.contrib.admin -- 管理员站点， 你很快就会使用它。
* django.contrib.auth -- 认证授权系统。
* django.contrib.contenttypes -- 内容类型框架。
* django.contrib.sessions -- 会话框架。
* django.contrib.messages -- 消息框架。
* django.contrib.staticfiles -- 管理静态文件的框架。

```bash
➜  myweb git:(master) ✗ python manage.py migrate
```
这个migrate命令检查INSTALLED_APPS设置,为其中的每个应用穿件需要的数据表.

#### 创建模型
在Django里写一个数据库驱动的Web应用第一步是定义模型-也就是数据库结构设计和附加的其他元数据.
```python
from django.db import models

# Create your models here.
class Question(models.Model):
    question_text = models.CharField(max_length=200)
    pub_date = models.DateTimeField('data published')

class Choice(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    choice_text = models.CharField(max_length=200)
    votes = models.IntegerField(default=0)
```
#### 激活模型
* 为这个应用创建schema(生成CREATE TEABLE语句).
* 创建可以与Question和Choice对象进行交互的Python数据库API
但是首先得把polls应用安装到项目里面
为了在我们的工程中包含这个应用,我们需要配置类INSTALL_APPS中添加设置.
因为PollsConfig类写在polls/apps.py中,所以它的点式路径是'polls.apps.PollsConfig'.
在文件mysite/settings.py中INSTALL_APPS添加点式路径.
```bash
➜  myweb git:(master) ✗ python manage.py makemigrations polls
Migrations for 'polls':
  polls/migrations/0001_initial.py:
    - Create model Choice
    - Create model Question
    - Add field question to choice
```
通过makemigrations命令,Django会检测你对模型文件的修改,并且把修改的部分存储为一次迁移
**迁移(migration)**是Django对于模型定义(也就是数据库结构)的变化的存储形式,也只是磁盘上的文件
Django有一个自动执行数据库迁移并同步管理数据库机构的命令
```bash
➜  myweb git:(master) ✗ python manage.py sqlmigrate polls 0001
BEGIN;
--
-- Create model Choice
--CREATE TABLE "polls_choice" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "choice_text" varchar(200) NOT
 NULL, "votes" integer NOT NULL);
--
-- Create model Question
--
CREATE TABLE "polls_question" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "question_text" varchar(200) NOT NULL, "pub_date" datetime NOT NULL);
--
-- Add field question to choice
--
ALTER TABLE "polls_choice" RENAME TO "polls_choice__old";
CREATE TABLE "polls_choice" ("id" integer NOT NULL PRIMARY KEY AUTOINCREMENT, "choice_text" varchar(200) NOT NULL, "votes" integer NOT NULL, "question_id" integer NOT NULL REFERENCES "polls_question" ("id") DEFERRABLE INITIALLY DEFERRED);
INSERT INTO "polls_choice" ("id", "choice_text", "votes", "question_id") SELECT "id", "choice_text", "votes", NULL FROM "polls_choice__old";
DROP TABLE "polls_choice__old";
CREATE INDEX "polls_choice_question_id_c5b4b260" ON "polls_choice" ("question_id");
COMMIT;
```
请注意一下几点:
* 输出内容和谁用的数据库有关,上面的输出示例用的是PostgreSQL
* 数据库的表名是由应用名(polls)和模型名的小写形式(question和choice)连接而来.
* 主键(IDs)会被自动创建(也可以自己定义).
* 默认的,Django会在外键字段名后追加字符串"_id".
* 外键关系由FOREIGN KEY生成.不用关心DEFERRABLE部分,它只告诉PostgreSql,请在事务全都执行完后在创建外键关系
* 生成的SQL语句是为你所用的数据库定制的,所以哪些和数据库有关的字段类型,比如auto_increment(MySQL),serial(PostgreSQL)和integer primary key autoincrement(SQLite),Django会帮你自动处理.哪些和引号相关的事情-例如,是使用单引号还是双引号,一样会被自动处理
* 这个sqlmigrate命令并没有真正在你的数据库中执行迁移,它只是把命令输出到屏幕上,让你看看Django认为需要执行哪些SQL语句.这在你想看看Django到底准备做什么,或者当你是数据库管理员,需要写脚本来批量处理数据库时会很有用.

python manage.py check ;这个命令帮助你检查项目中的问题，并且在检查过程中不会对数据库进行任何操作。

现在再次运行migrate命令,在数据库里创建新定义的模型的数据表
```bash
➜  myweb git:(master) ✗ python manage.py migrate
Operations to perform:
  Apply all migrations: admin, auth, contenttypes, polls, sessions
Running migrations:
  Applying contenttypes.0001_initial... OK
  Applying auth.0001_initial... OK
  Applying admin.0001_initial... OK
  Applying admin.0002_logentry_remove_auto_add... OK
  Applying admin.0003_logentry_add_action_flag_choices... OK
  Applying contenttypes.0002_remove_content_type_name... OK
  Applying auth.0002_alter_permission_name_max_length... OK
  Applying auth.0003_alter_user_email_max_length... OK
  Applying auth.0004_alter_user_username_opts... OK
  Applying auth.0005_alter_user_last_login_null... OK
  Applying auth.0006_require_contenttypes_0002... OK
  Applying auth.0007_alter_validators_add_error_messages... OK
  Applying auth.0008_alter_user_username_max_length... OK
  Applying auth.0009_alter_user_last_name_max_length... OK
  Applying polls.0001_initial... OK
  Applying sessions.0001_initial... OK
```
这个migrate命令选中所有还没有执行过的迁移(Django通过在数据库中创建一个特殊的表django_migrations来跟踪执行过哪些迁移)并应用在数据库上-也就是将对象模型的更改同步到数据库结构上

迁移是非常强大的功能,它能让你在开发过程中持续的改变数据库结构而不需要重新删除和创建表-它专注于数据库平滑升级而不会丢失数据.
改变模型需要三步:
* 编辑models.py文件,改变模型
* 运行python manage.py makemigrations为模型的改变生成迁移文件.
* 运行python manage.py migrate来应用数据库迁移

数据库迁移被分解生成和应用两个命令是为了让你能够在代码控制系统上提交迁移数据并使其能在多个应用里使用.

#### 初试API
进入交互python命令行,尝试一下Django创建的各种API.
使用这个命令而不简单使用"python"是因为manage.py会设置DJANGO_SETTINGS_MODULE环境变量,这个变量会让Django根据mysite/settings.py文件来设置Python包的导入路径.
```bash
➜  myweb git:(master) ✗ python manage.py shell
Python 3.6.5 |Anaconda, Inc.| (default, Apr 29 2018, 16:14:56)
Type 'copyright', 'credits' or 'license' for more information
IPython 6.4.0 -- An enhanced Interactive Python. Type '?' for help.

In [1]: from polls.models import Choice, Question
# No questions are in the system yet.
In [2]: Question.objects.all() 
Out[2]: <QuerySet []>
# Create a new Question.
# Support for time zones is enabled in the default settins file, so
# Django expects a datetime with tzinfo for pub_data.Use timezone.Now()
# instead of datetime.datatime.now() and it will do the right thing.
In [3]: from django.utils import timezone
In [6]: q = Question(question_text="What's new?", pub_date=timezone.now())
# Save the object into the database.You have to call save() explicitly.
In [7]: q.save()
# Now it has an ID.
In [ ]: q.id
Out[ ]: 1
# Access model field values via Python attributes.
In [8]: q.question_text
Out[8]: "What's new?"
In [9]: q.pub_date
Out[9]: datetime.datetime(2019, 1, 10, 9, 47, 43, 192475, tzinfo=<UTC>)
# objects.all() displays all the questions in the database.
In [10]: Question.objects.all()
Out[10]: <QuerySet [<Question: Question object (1)>]>
```
<Question: Question object (1)>对于我们了解这个对象的细节没有什么帮助.让我们通过编辑Question模型的代码(位于polls/models.py中)来修复这个问题.给Question和Choice增加__str__()方法.

```python
class Question(models.Model):
    # ...
    def __str__(self):
        return self.question_text

class Choice(models.Model):
    # ...
    def __str__(self):
        return self.choice_text
```
新加入的import datetime和from django.utils import timezone分贝导入了Python的标准datetime模块和Django中和时区相关的django.utils.timezone工具模块.保存文件然后通过python manage.py shell命令再次打开Python交互式命令行
```bash
>>> from polls.models import Choice, Question

# Make sure our __str__() addition worked.
>>> Question.objects.all()
<QuerySet [<Question: What's up?>]>

# Django provides a rich database lookup API that's entirely driven by
# keyword arguments.
>>> Question.objects.filter(id=1)
<QuerySet [<Question: What's up?>]>
>>> Question.objects.filter(question_text__startswith='What')
<QuerySet [<Question: What's up?>]>

# Get the question that was published this year.
>>> from django.utils import timezone
>>> current_year = timezone.now().year
>>> Question.objects.get(pub_date__year=current_year)
<Question: What's up?>

# Request an ID that doesn't exist, this will raise an exception.
>>> Question.objects.get(id=2)
Traceback (most recent call last):
    ...
DoesNotExist: Question matching query does not exist.

# Lookup by a primary key is the most common case, so Django provides a
# shortcut for primary-key exact lookups.
# The following is identical to Question.objects.get(id=1).
>>> Question.objects.get(pk=1)
<Question: What's up?>

# Make sure our custom method worked.
>>> q = Question.objects.get(pk=1)
>>> q.was_published_recently()
True

# Give the Question a couple of Choices. The create call constructs a new
# Choice object, does the INSERT statement, adds the choice to the set
# of available choices and returns the new Choice object. Django creates
# a set to hold the "other side" of a ForeignKey relation
# (e.g. a question's choice) which can be accessed via the API.
>>> q = Question.objects.get(pk=1)

# Display any choices from the related object set -- none so far.
>>> q.choice_set.all()
<QuerySet []>

# Create three choices.
>>> q.choice_set.create(choice_text='Not much', votes=0)
<Choice: Not much>
>>> q.choice_set.create(choice_text='The sky', votes=0)
<Choice: The sky>
>>> c = q.choice_set.create(choice_text='Just hacking again', votes=0)

# Choice objects have API access to their related Question objects.
>>> c.question
<Question: What's up?>

# And vice versa: Question objects get access to Choice objects.
>>> q.choice_set.all()
<QuerySet [<Choice: Not much>, <Choice: The sky>, <Choice: Just hacking again>]>
>>> q.choice_set.count()
3

# The API automatically follows relationships as far as you need.
# Use double underscores to separate relationships.
# This works as many levels deep as you want; there's no limit.
# Find all Choices for any question whose pub_date is in this year
# (reusing the 'current_year' variable we created above).
>>> Choice.objects.filter(question__pub_date__year=current_year)
<QuerySet [<Choice: Not much>, <Choice: The sky>, <Choice: Just hacking again>]>

# Let's delete one of the choices. Use delete() for that.
>>> c = q.choice_set.filter(choice_text__startswith='Just hacking')
>>> c.delete()
```
#### 介绍管理页面
Django全自动地根据模型创建后台界面.

###### 创建一个管理员账号
```bash
➜  myweb git:(master) ✗ python manage.py createsuperuser 
Username (leave blank to use 'example'): admin
Email address: name@outlook.com
Password: 
Password (again): 
Superuser created successfully.
```
###### 启动开发服务器
Django的管理界面默认就是启动的,如果开发服务器未启动,用以下命令启动它.
```bash
➜  myweb git:(master) ✗ python manage.py runserver
```
###### 进入管理站点页面
登陆后,你将会看到集中可编辑的内容: 用户和组.它们是由django.contrib.auth提供的,这是Django开发的认证框架
###### 向管理页面中加入投票应用
投票应用并没有在索引页面里显示
只需要做一件事: 告诉管理页面,问题Question对象需要被管理.打开polls/admin.py文件
```python
from django.contrib import admin
from .models import Question
# Register your models here.
admin.site.register(Question)
```
重新加载后
![register_question](register_question.png)
###### 体验便捷的管理功能
现在我们向管理页面注册了问题Question类.Django知道它应该被显示在索引页里:
注意事项:
* 这个表单是从问题Question模型中自动生成的
* 不同的字段类型(日期时间段DateTimeField,字符字段CharField)会生成对应的HTML输入控件.每个类型字段都知道它们该如何在管理页面显示自己
* 每个日期时间段DateTimeField都有JavaScript写的快捷按钮.日期有转到今天(Today)的快捷键和一个弹出式日历界面.时间有设为现在(Now)的快捷键和一个列出常用时间的方便的弹出式列表
页面底部提供了几个选项:
* 保存(Save) -保存改变,然后返回对象列表
* 保存并继续编辑（Save and continue editing） - 保存改变，然后重新载入当前对象的修改界面。
* 保存并新增（Save and add another） - 保存改变，然后添加一个新的空对象并载入修改界面。
* 删除（Delete） - 显示一个确认删除页面。

## part3