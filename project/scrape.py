from bs4 import BeautifulSoup # need pip install bs4
from urllib.request import Request, urlopen
import urllib.request
import re

github_url = "https://github.com/search?q=created%3A2020-07-01" + \
                         "+created%3A2020-07-31&type=Repositories "



def scrape (url):
    

    r_object = urllib.request.urlopen(url)
    soup = BeautifulSoup(r_object, 'html.parser')

    t = soup.findAll('a', {'class': 'filter-item'})
    count = 0
    a = []

    for text in t:
        a.append(text.text.replace(" ", '').replace("\n", '').replace(",",""))

    final = {}
    a1 = []
    a2 = []

    for el in a:
        num = int(re.search(r'\d+', el).group())
        s = re.sub(r'\d+', '', el)

        final[s] = num
        a1.append(num)
        a2.append(s)


    print(a1)
    print(a2)
    return a1,a2

scrape(github_url)
#print(aa1)
#print(aa1[0])
#print(aa1[1])