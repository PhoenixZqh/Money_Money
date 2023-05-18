import torch
import torchvision
from torch import nn

# train_data = torchvision.datasets.ImageNet(
#     "data_imagenet",
#     split='train',
#     transform=torchvision.transforms.ToTensor(),
#     download=True)

vgg16_true = torchvision.models.vgg16(pretrained=True)

train_data = torchvision.datasets.CIFAR10(
    "dataset",
    train=True,
    transform=torchvision.transforms.ToTensor(),
    download=True)

# 如何使用现有网络，适配自己的项目
# vgg16_true.add_module('add_linear', nn.Linear(1000, 10))  #1000个分类变成10分类
vgg16_true.classifier.add_module('add_linear', nn.Linear(1000, 10))
print(vgg16_true)