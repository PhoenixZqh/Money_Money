import torch
import torchvision
from torch import nn
from torch.nn import Conv2d, MaxPool2d, Flatten, Linear, Sequential, CrossEntropyLoss
from torch.utils.tensorboard import SummaryWriter
from torch.utils.data import DataLoader

dataset = torchvision.datasets.CIFAR10(
    "dataset",
    train=False,
    transform=torchvision.transforms.ToTensor(),
    download=True)
dataloader = DataLoader(dataset, batch_size=1)


class zModel(nn.Module):

    def __init__(self) -> None:
        super(zModel, self).__init__()
        # self.conv1 = Conv2d(3, 32, 5, padding=2)
        # self.maxpool1 = MaxPool2d(2)
        # self.conv2 = Conv2d(32, 32, 5, padding=2)
        # self.maxpool2 = MaxPool2d(2)
        # self.conv3 = Conv2d(32, 64, 5, padding=2)

    def __init__(self) -> None:
        super(zModel, self).__init__()
        # self.conv1 = Conv2d(3, 32, 5, padding=2)
        # self.maxpool1 = MaxPool2d(2)
        # self.conv2 = Conv2d(32, 32, 5, padding=2)
        # self.maxpool2 = MaxPool2d(2)
        # self.conv3 = Conv2d(32, 64, 5, padding=2)

    def __init__(self) -> None:
        super(zModel, self).__init__()
        # self.conv1 = Conv2d(3, 32, 5, padding=2)
        # self.maxpool1 = MaxPool2d(2)
        # self.conv2 = Conv2d(32, 32, 5, padding=2)
        # self.maxpool2 = MaxPool2d(2)
        # self.conv3 = Conv2d(32, 64, 5, padding=2)
        # self.maxpool3 = MaxPool2d(2)
        # self.flatten = Flatten()  # 展开后1024 ， 64×4×4
        # self.linear1 = Linear(1024, 64)
        # self.linear2 = Linear(64, 10)
        self.model1 = Sequential(Conv2d(3, 32, 5, padding=2), MaxPool2d(2),
                                 Conv2d(32, 32, 5, padding=2), MaxPool2d(2),
                                 Conv2d(32, 64, 5, padding=2), MaxPool2d(2),
                                 Flatten(), Linear(1024, 64),
                                 Linear(64, 10))  # 采用sequential的方式构建网络

    def forward(self, x):
        # x = self.conv1(x)
        # x = self.maxpool1(x)
        # x = self.conv2(x)
        # x = self.maxpool2(x)
        # x = self.conv3(x)
        # x = self.maxpool3(x)
        # x = self.flatten(x)
        # x = self.linear1(x)
        # x = self.linear2(x)
        x = self.model1(x)

        return x


loss = CrossEntropyLoss()
model = zModel()
# print(model)
optimizer = torch.optim.SGD(
    model.parameters(),
    lr=0.01,
)

# 检查网络有效性
input = torch.ones(64, 3, 32, 32)  # batch, channel,H,W
output = model(input)
print(output.shape)

writer = SummaryWriter("logs")
writer.add_graph(model, input)
writer.close()

for epoch in range(20):
    running_loss = 0.0

    for data in dataloader:
        optimizer.zero_grad()
        imgs, targets = data
        output = model(imgs)
        # print(targets)  #真实target
        # print(output)   # 预测值
        res = loss(output, targets)
        res.backward()  # 反向传播得到对应参数的梯度
        optimizer.step()  # 对模型参数进行调优

        running_loss += res
    print(running_loss)
