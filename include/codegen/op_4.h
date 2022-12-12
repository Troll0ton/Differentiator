
CMD_DEF(SIN, "sin",
{
    Node *right_node_c = COPY_RIGHT;

    val.op = COS;

    INIT_NODE (new_node_1, NULL, right_node_c, NULL, OP, val, 4);

    val.op = MUL;

    ASSIGN_NODE (curr_node, new_node_1, CALC_DRV (RIGHT_NODE), curr_node->parent, OP, val, 2);

    return curr_node;
})

CMD_DEF(COS, "cos",
{
    Node *right_node_c = COPY_RIGHT;

    val.op = SIN;

    INIT_NODE (new_node_sin, NULL, right_node_c, NULL, OP, val, 4);

    val.num = -1;

    INIT_NODE (node_one, NULL, NULL, NULL, NUM, val, 4);

    val.op = MUL;

    INIT_NODE (new_node_1, node_one, new_node_sin, NULL, OP, val, 2);

    val.op = MUL;

    ASSIGN_NODE (curr_node, new_node_1, CALC_DRV (RIGHT_NODE), curr_node->parent, OP, val, 2);

    return curr_node;
})

CMD_DEF(LN, "ln",
{
    ;
})

CMD_DEF(TG, "tg",
{
    ;
})

CMD_DEF(CTG, "ctg",
{
    ;
})

CMD_DEF(ARCSIN, "arcsin",
{
    ;
})

CMD_DEF(ARCCOS, "arccos",
{
    ;
})

CMD_DEF(ARCTG, "arctg",
{
    ;
})

CMD_DEF(ARCCTG, "arcctg",
{
    ;
})
