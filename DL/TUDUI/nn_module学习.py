from torch import nn
import torch


class zModel(nn.Module):

    def __init__(self) -> None:
        super().__init__()

    def forward(self, input):
        output = input + 1
        return output


model = zModel()

x = torch.tensor(1.0)
output = model(x)
print(output)