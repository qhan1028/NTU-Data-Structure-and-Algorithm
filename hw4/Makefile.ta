CC=g++
FNAME=heart.train
PNAME=heart.test
EPSILON=0.05
T=50
RM=rm -rf

.PHONY: clean_tree_pred_func clean_forest_pred_func run_tree run_forest predict_tree predict_forest clean

tree_pred_func.cpp: tree $(FNAME)
	./tree $(FNAME) $(EPSILON) > $@

clean_tree_pred_func: 
	$(RM) tree_pred_func.cpp
                      
forest_pred_func.cpp: forest $(FNAME)
	./forest $(FNAME) $(T) > $@

clean_forest_pred_func: 
	$(RM) forest_pred_func.cpp

predict_tree: tree_predictor.cpp tree_pred_func.cpp $(PNAME)
	$(CC) tree_predictor.cpp tree_pred_func.cpp -o tree_predictor
	./tree_predictor $(PNAME) > ./tree_prediction.txt

run_tree: clean_tree_pred_func predict_tree

predict_forest: forest_predictor.cpp forest_pred_func.cpp $(PNAME)
	$(CC) forest_predictor.cpp forest_pred_func.cpp -o forest_predictor
	./forest_predictor $(PNAME) > ./forest_prediction.txt

run_forest: clean_forest_pred_func predict_forest

clean:
	$(RM) tree_predictor forest_predictor tree_pred_func.cpp forest_pred_func.cpp

