# Reproducing interesting (not only) deep learning papers


### Dense & CNN for sentiment classification

Based on two papers by Yoon Kim [1] and Xiang Zhang et. al [2] I created three neural network architecture: (i) character-level CNN, (ii) world-level CNN, (iii) hybrid approach combining DNN and word-level CNN for the sentiment classification task. The results on the movie review dataset show a slight improvement in merging networks for that task e.g. (iii). For more information take a look at my [report](conv_net_text_classification/Robert_Jankowski_CNN_Sentiment_Classification.pdf).

[1] Kim, Yoon. "Convolutional Neural Networks for Sentence Classification." Proceedings of the 2014 Conference on Empirical Methods in Natural Language Processing (EMNLP). 2014.
[2] Zhang, Xiang, Junbo Zhao, and Yann LeCun. "Character-level convolutional networks for text classification." Advances in neural information processing systems. 2015.

### CNN for complex network classification

In paper by Xin et. al [1] the authors first embedded network using DeepWalk algorithm into 2-dimensional space. The rasterized image from 2D-embeddings was the input for CNN. In the last step, I've used a different approach, namely, I plot 2D embeddings using matplotlib and with OpenCV, I converted that image into the input to CNN. The network tried to distinguish images from two complex networks: (1) Barabasi-Albert model and (2) Watts-Strogatz model. The results in case of accuracy and AUC were respectively 0.82 and 0.91.

[1] Xin, Ruyue, Jiang Zhang, and Yitong Shao. "Complex network classification with convolutional neural network." Tsinghua Science and Technology 25.4 (2020): 447-457.

### Hate detection in social media

