
/** Get linear equivlent to foo[i][j] operator, get element in row wise.
 * 
 * @param{i} int
 * @param{j} int
 * @param{n} int - number of rows
 */
export function IdRw(i, j, n) {
    return (i*n + j)
}