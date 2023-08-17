import time

import torch
import torchvision
from torch import nn
from torch.nn import Sequential, MaxPool2d, Flatten, Linear, Conv2d
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter

from model import *

#定义训练的设备
device = torch.device("cuda")

train_data = torchvision.datasets.CIFAR10("../dataset", train=True, transform=torchvision.transforms.ToTensor(),
                                          download=True)
test_data = torchvision.datasets.CIFAR10("../dataset", train=False, transform=torchvision.transforms.ToTensor(),
                                         download=True)

# 测试数据集大小
train_data_size = len(train_data)
test_data_size = len(test_data)

print("训练集大小为：{}".format(train_data_size), "\n", "测试集大小为：{}".format(test_data_size))  # format() 格式化字符串

train_data_loader = DataLoader(train_data, batch_size=64)
test_data_loader = DataLoader(test_data, batch_size=64)

# 创建网络模型
model = zModel()
model = model.to(device)
# if torch.cuda.is_available():  # 判断cuda是否可用
#     model = model.cuda()  # 使用GUP训练

lossFN = nn.CrossEntropyLoss()  # 定义损失函数
lossFN = lossFN.to(device)
# if torch.cuda.is_available():
#     lossFN = lossFN.cuda()

learning_rate = 0.01
optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)  # 定义优化器

total_train_step = 0  # 记录训练的次数
total_test_step = 0

epoch = 20  # 训练10轮

writer = SummaryWriter("../logs")
start_time = time.time()

for i in range(epoch):
    print("*********第{}轮训练开始*********".format(i + 1))

    model.train()  # 训练步骤开始
    for data in train_data_loader:
        imgs, targets = data
        imgs = imgs.to(device)
        targets = targets.to(device)
        # if torch.cuda.is_available():
        #     imgs = imgs.cuda()
        #     targets = targets.cuda()
        output = model(imgs)
        loss = lossFN(output, targets)

        # 优化器调优
        optimizer.zero_grad()  # 首先要进行梯度清零
        loss.backward()
        optimizer.step()

        total_train_step += 1
        if total_train_step % 100 == 0:
            end_time = time.time()
            print("耗时:", end_time - start_time)
            print("训练次数：{}，Loss:{}".format(total_train_step, loss))
            writer.add_scalar("train_loss", loss.item(), total_train_step)

    # 每轮训练完，在测试集上验证
    model.eval()  # 测试步骤开始
    total_loss = 0
    total_accuracy = 0
    tmp = 0

    with torch.no_grad():
        for data in test_data_loader:
            imgs, targets = data
            imgs = imgs.to(device)
            targets = targets.to(device)
            # if torch.cuda.is_available():
            #     imgs = imgs.cuda()
            #     targets = targets.cuda()
            output = model(imgs)
            loss = lossFN(output, targets)
            total_loss += loss
            accuracy = (output.argmax(1) == targets).sum()  # 计算正确的个数
            total_accuracy += accuracy
    print("整体测试集上loss:{}".format(total_loss))
    print("测试集正确率：{}".format(total_accuracy / test_data_size))
    writer.add_scalar("test_loss", total_loss, total_test_step)
    accuracy_final = total_accuracy / test_data_size
    writer.add_scalar("accuracy", accuracy_final, total_test_step)
    total_test_step += 1

    # torch.save(model, "../model/zqh_train{}.pth".format(i))
    if accuracy_final > tmp:
        max_accuracy = i
        tmp = accuracy_final
torch.save(model.state_dict(), "../model/zqh_train{}.pth".format(max_accuracy))  # 保存每一轮训练的模型,官方推荐方式

writer.close()
