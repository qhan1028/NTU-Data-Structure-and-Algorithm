3.2(1)
function (stack S, queue Q) {
found = 0
for i from 1 to N
	pop element from S
	if the element popped from S is equal to x
		found = 1
	end if 
	push the element to Q
end for 
push all elements "popped from Q" to S
push all elements "popped from S" to Q
push all elements "popped from Q" to S
return found
}
3.2(2)
push_back all elements "popped from S" to D
push_back all elements "popped from T" to D
push_back all elements "popped_back from D" to S
3.2(3)
let one stack have all elements, the other stack is used to be a buffer
function pop_front() {
	push all elements "popped from stack" to tmp_stack
	if not stack.isempty
		pop one element from stack
	end if
	push all elements "popped from tmp_stack" to stack
}
function push_front(element) {
	push all elements "popped from stack" to tmp_stack
	push element to tmp_stack
	push all elements "popped from tmp_stack" to stack
}
function pop_back() {
	if not stack.isempty
		pop one element from stack
	end if
}
function push_back(element) {
	push element to stack
}
3.3(1)

3.3(2)
vector result
array card[]
for i from n to 1
	rand_num = randomInteger(i)
	swap (card[i], card[rand_num])
	push_back card[i] to result
end for