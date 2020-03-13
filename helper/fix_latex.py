import re
import unicodedata
def fix(data):
    data = unicodedata.normalize("NFKD", data)
    data = data.replace('\r','')
    # add space after punctuation
    punctuation = r'[,\.\?!;:]'
    data = re.sub(r'(' + punctuation + r')', r'\1 ', data)

    # \textbf{ s } -> $s$
    data = re.sub(r'\\textbf\{\s*(\w)\s*\}', r'$\1$', data)
    # remove continuous space
    data = re.sub(r' +', ' ', data)
    # remove space before punctuation
    data = re.sub(r'\s+(' + punctuation + r')', r'\1', data)

    # remove space after (
    data = re.sub(r'\(\s+','(',data)
    # remove space before )
    data = re.sub(r'\s+\)',')',data)
    # replace 1ex -> 10^{x}
    data = re.sub(r'1e(\d+)', r'10^{\1}', data)
    # replace xey -> x * 10^{y}
    data = re.sub(r'(\d+)e(\d+)', r'\1 \\times 10^{\2}', data)
    # remove space in the end of line
    data = data.replace(' \n', '\n')
    # remove space in the beginning of line
    data = data.replace('\n ', '\n')

    data = data.replace('≤', '$\\leq$')
    data = data.replace('<=', '$\\leq$')
    data = data.replace('>=', '$\\geq$')
    data = data.replace('π', '$\pi$')
    data = data.replace('...', ' \dots')
    data = data.replace('->', '$\\rightarrow$')

    left = r'[\(\)\[\] \n,\.:]'
    # replace number by $number$ 
    data = re.sub(r'(' + left + r')(\d+)(' + left + ')', r'\1$\2$\3', data)
    # replace single charractor x by $x$
    data = re.sub(r'(' + left + r')(\w)(' + left + ')', r'\1$\2$\3', data)
    # add space before and after $
    data = data.replace('$', ' $ ')
    # remove continuous space again
    data = re.sub(r' +', ' ', data)
    # replace $space$ to space
    data = data.replace('$ $', ' ')
    # replce $ x $ to $x$
    data = re.sub(r'\$\s+([^\$]+)\s+\$', r'$\1$', data)
    # add space after punctuation (again)
    data = re.sub(r'(' + punctuation + r')', r'\1 ', data)
    # remove continuous space again
    data = re.sub(r' +', ' ', data)
     # remove space before punctuation (again)
    data = re.sub(r'\s+(' + punctuation + r')', r'\1', data)

    # remove space after ( (again)
    data = re.sub(r'\(\s+','(',data)
    # remove space before ) (again)
    data = re.sub(r'\s+\)',')',data)

    return data
if __name__ == '__main__':
    data = fix(open("statement.txt", "r", encoding="utf-8").read())
    with open("statement.txt", "w", encoding="utf-8") as OUT: OUT.write(data)
