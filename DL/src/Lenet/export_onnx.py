import torch.nn as nn
import torch.nn.functional as F
import torch
from lenet import *

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# class LeNet(nn.Module):

#     def __init__(self):
#         super(LeNet, self).__init__()
#         self.conv = nn.Sequential(
#             nn.Conv2d(in_channels=1, out_channels=6,
#                       kernel_size=5),  # in_channels, out_channels, kernel_size
#             nn.LeakyReLU(0.1),
#             nn.MaxPool2d(2, 2),  # kernel_size, stride
#             nn.Conv2d(6, 16, 5),
#             nn.LeakyReLU(0.1),
#             nn.MaxPool2d(2, 2))
#         self.fc = nn.Sequential(nn.Linear(16 * 4 * 4, 120), nn.LeakyReLU(0.1),
#                                 nn.Linear(120, 84), nn.ReLU(),
#                                 nn.Linear(84, 10))

#     def forward(self, img):
#         feature = self.conv(img)
#         output = self.fc(feature.view(img.shape[0], -1))
#         return output

lenet_model = LeNet()
lenet_model = torch.load("./workspace/model/lenet.pth")
lenet_model.eval()

lenet_model = lenet_model.to(device)

dummy_input = torch.randn(1, 1, 32, 32)
dummy_input = dummy_input.to(device)

onnx_path = "./workspace/model/lenet.onnx"

torch.onnx.export(lenet_model, dummy_input, onnx_path, verbose=True)
