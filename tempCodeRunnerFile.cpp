   while (!ops.empty()) {
        double val2 = values.top();
        values.pop();
        
        double val1 = values.top();
        values.pop();
        
        char op = ops.top();
        ops.pop();
        
        values.push(applyOperation(val1, val2, op));
    }
    
    return values.top();
}