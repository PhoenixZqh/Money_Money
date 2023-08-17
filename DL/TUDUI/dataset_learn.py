from torch.utils.data import Dataset
from PIL import Image
import os
import cv2

class MyData(Dataset):
    def __init__(self,root_dir,label_dir):
        self.root_dir = root_dir
        self.label_dir = label_dir
        self.path = os.path.join(self.root_dir,self.label_dir)  #join , 将路径拼接在一起
        self.img_path = os.listdir(self.path)
        
    def __getitem__(self,idx):
        img_name = self.img_path[idx]
        img_item_path = os.path.join(self.root_dir,self.label_dir,img_name)
        img = Image.open(img_item_path)
        label = self.label_dir
        
        return img,label
    
    def __len__(self):
        return len(self.img_path)
    

root_dir = "hymenoptera_data/train"
ant_label_dir = "ants"
ant_dataset = MyData(root_dir, ant_label_dir)