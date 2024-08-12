# 卡尔曼滤波公式推导

1. 根据上节得到状态空间方程

   $$
   \begin{align}
   \color{green}\dot X_t &= \color{green}AX_{t-1}+BU_{t-1}+W_{t-1}\tag1 \\
   \color{green} Z_t &= \color{green}H.X_t+V_t\tag2
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
   令G=K_tH,\quad &\hat X_{t} = \hat X_{t^-} + K_t(Z_t-H\hat X_{t^-})\tag3\\
   \\
   当K_t=0时，更相信预测值， 当Kt=H^-时， 更相信测量值\\
   \end{align*}
   $$

   **目标： 希望融合后的结果无限接近真实值**

   $$
   令e_t = X_t - \hat X_t
   $$

   $$
   \begin{align*}
   根据公式23, \quad X_t - \hat X_t &= X_t - \hat X_{t^-} - K_tHX_t -K_tV_t + K_tH\hat X_{t^-}\\
   &= (I-K_tH)(X_t-\hat X_{t^-})-K_tV_t\\
   &= (I-K_tH){\color{purple}e_{t^-}} - K_tV_t\tag4
   \end{align*}
   $$

   $$
   \left \{
   \begin{array}{c}
   \boxed{(AB)^T=B^TA^T}\\
   \boxed{(A+B)^T = A^T+B^T}\tag5
   \end{array}
   \right.
   $$

   4.t时刻的误差协方差矩阵

   $$
   \begin{align*}
   根据公式4，5, \quad
   P_{e_t} &= \epsilon[e_te_{t}^T]\\
   &=\epsilon[(X_t-\hat X_t)(X_t-\hat X_t)^T]\\
   &=\epsilon[[(I-K_tH)e_{t^-}-K_tV_t][(I-K_tH)e_{t^-}-K_tV_t]^T]\\
   &=\epsilon[[(I-K_tH)e_{t^-}-K_tV_t][e_{t^-}^T(I-K_tH)^T-V_t^TK_t^T]]\\
   &=\epsilon[(I-K_tH)e_{t^-}e_{t^-}^T(I-K_tH)^T-(I-K_tH)e_{t^-}V_t^TK_t^T-K_tV_te_{t^-}^T(I-K_tH)^T+K_tV_tV_t^TK_t^T]\\
   &=\epsilon(I-K_tH)e_{t^-}e_{t^-}^T(I-K_tH)^T-\boxed {\epsilon(I-K_tH)e_{t^-}V_t^TK_t^T-\epsilon K_tV_te_{t^-}^T(I-K_tH)^T}+\epsilon K_tV_tV_t^TK_t^T]\\
   对于画框的两项，\epsilon(I-K_tH)e_{t^-}V_t^TK_t^T = (I-K_tH)\epsilon e_{t^-}\epsilon V_t^TK_t^T, \ e_t V_t^T 都服从正态分布， 期望为0， 则有：\\
   &=(I-K_tH)\boxed{\epsilon e_{t^-}e_{t^-}^T}(I-K_tH)^T+K_t\boxed {\epsilon V_tV_t^T}K_t^T\\
   对于画框的两项， 分别为t时刻误差的先验和测量误差协方差矩阵：\\
   &=(I-K_tH)P_{e_t}^-(I-K_tH)^T+K_tRK_t^T\\
   &=P_{e_t}^- -K_tHP_{e_t}^-(I^T-H^TK_t^T)+K_tRK_t^T\\
   &=\color{green}P_{e_t}^--K_tHP_{e_t}^--P_{e_t}^-H^TK_t^T+K_tHP_{e_t}^-H^TK_t^T+K_tRK_t^T\tag6\\
   对于(-P_{e_t}^-H^TK_t^T)^T=K_tHP_{e_t}^-, P_{e_t}^-是对角矩阵，转置前后相同，\\
   &=P_{e_t}^--2K_tHP_{e_t}^-+K_tHP_{e_t}^-H^TK_t^T+K_tRK_t^T\tag7
   \end{align*}
   $$

   考虑一个随机变量X，其协方差矩阵为Σ， 该向量的方差可以表示为 Var(X)=Tr(Σ)；这个结论源自于协方差矩阵的定义：**协方差矩阵的对角线上的元素是每个随机变量的方差，因此它们的和等于方差向量的迹。**

   $$
   \left \{
   \begin{array}{c}
   \frac {d tr(AB)}{dA}=B^T\\
   \frac {dABA}{dA} = 2AB\tag8
   \end{array}
   \right.
   $$

   根据上述结论以及公式8，要时的误差最小， 迹最小

   $$
   \frac {d tr(P_{e_t})}{dK_t} = 0 - 2(HP_t^-)^T+2K_tHP_t^-H^T+2K_tR=0
   $$

   得到卡尔曼增益：

   $$
   \color {green} K_t = \frac {P_t^-H^T}{HP_t^-H^T+R}\tag9
   $$

   $$
   \begin{align*}
   预测误差协方差矩阵，\ e_t^- &= X_t-\hat X_t^- \\
   &=AX_{t-1} + BU_{t-1}+W_{t-1} - A\hat X_{t-1}-BU_{t-1}\\
   &=A(X_{t-1}-\hat X_{t-1})+W_{t-1}\\
   &=Ae_{t-1}+W_{t-1}\\

   P_t^- &= \epsilon [e_t^-(e_t^-)^T]\\
   &= \epsilon [(Ae_{t-1}+W_{t-1})(Ae_{t-1}+W_{t-1})^T]\\
   &= \epsilon [(Ae_{t-1}+W_{t-1})(e_{t-1}^TA^T+W_{t-1}^T)]\\
   &= \epsilon [Ae_{t-1}e_{t-1}^TA^T+\boxed {Ae_{t-1}W_{t-1}^T+W_{t-1}e_{t-1}^TA^T}+W_{t-1}W_{t-1}^T]\\
   e_{t-1}和W_{t-1}相互独立，期望为0，\ & = A\epsilon e_{t-1}e_{t-1}^TA^T +\epsilon W_{t-1}W_{t-1}^T \\
   & = \color{green}AP_{t-1}A^T + Q \tag{10}
   \end{align*}
   $$
4. 得到卡尔曼滤波的5个步骤

   $$
   \left \{
   \begin{array}{c}
   \color{blue} \hat X_{t^-} &=& \color{blue} A\hat X_{t-1} + BU_{t-1} \\
   \color{blue}P_t^- &=& \color{blue} AP_{t-1}A^T + Q \\
   \color {blue} K_t &=& \color {blue} \frac {P_t^-H^T}{HP_t^-H^T+R}\\
   \color {blue}\hat X_{t} &=& \color {blue} \hat X_{t^-} + K_t(Z_t-H\hat X_{t^-})\\
   \color {blue}P_t &=& \color {blue} (I-K_tH)P_t^-
   \end{array}
   \right.
   $$
