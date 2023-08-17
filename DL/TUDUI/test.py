import torch
import torchvision

# vgg16 = torchvision.models.vgg16(pretrained=False)
# vgg16.load_state_dict(torch.load("model/vgg16_method2.pth"))
# print(vgg16)

model = torch.load("model/vgg16_method2.pth")
print(model)