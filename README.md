topx-update (Discontinued)
==========================

This project deals with identifying and incorporating best way of handling document updates in Top-X, a search engine developed at Max Planck Institute of Informatics. Recreating index for every change is not a viable solution, it uses a differential index which are later merged with primary index. The query processor uses both of these indices to determine fresh scores. Further, this project would extend to include mapReduce and co-processor framework. 
