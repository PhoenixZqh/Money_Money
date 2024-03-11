# 卡尔曼滤波公式推导

1. 根据上节得到状态空间方程

   $$
   \begin{align}
   \color{green}\dot X_t &= AX_{t-1}+BU_{t-1}+W_{t-1}\tag1 \\
   \color{green} Z_t &= H.X_t\tag2
   \end{align}
   $$

   $$
   \begin{align*}
   &A :状态转移矩阵\\
   &B :控制矩阵\\
   &U :控制输入\\
   &W :过程噪声 ～(0,Q)\\
   &H :观测矩阵\\
   &V ：测量噪声 ～(0,R) \\
   &\hat x_{t^-} ：t时刻的先验估计 \\
   &\hat x_t ： t时刻的后验
   \end{align*}
   $$
2. 可以得到预测的值和测量的值(忽略噪声的情况)

   $$
   \begin{align*}
   &\hat X_{t^-} = A\hat X_{t-1} + BU_{t-1} \\
   &\hat X_{mea} = H^- Z_t
   \end{align*}
   $$
3. 根据上节公式1，可以得到数据融合的结果

   $$
   \begin{align*}
   &\hat X_t = \hat X_{t^-} + G(H^-Z_t-\hat X{t^-})\\
   令G=K_tH,\quad &\hat X_{t} = \hat X_{t^-} + K_t(Z_t-H\hat X_{t^-})\\
   \\
   当K_t=0时，更相信预测值， 当Kt=H^-时， 更相信测量值\\
   \end{align*}
   $$

   **目标： 希望融合后的结果无限接近真实值**

4.
