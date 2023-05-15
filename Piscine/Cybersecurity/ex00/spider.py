import os
import sys
import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse

def scrap_links(links: set, depth: int, max_depth: int, base_url: str, followed_links: set) -> int:
	if depth > max_depth:
		return
	response = requests.get(base_url)
	soup = BeautifulSoup(response.content, 'html.parser')
	parsed_uri = urlparse(response.url)
	domain = '{uri.scheme}://{uri.netloc}'.format(uri=parsed_uri)
	for link in soup.find_all('a'):
		if link['href']:
			link_url = urljoin(domain, link['href'])
			link_parsed_uri = urlparse(link_url)
			link_domain = '{uri.scheme}://{uri.netloc}'.format(uri=link_parsed_uri)
			if domain == link_domain and link_url != domain:
				print("\r\033[KScrapped : {} (Total {})".format(link_url, len(links)), end='', flush=True)
				links.add(link_url)
				if link_url not in followed_links:
					followed_links.add(link_url)
					scrap_links(links, depth + 1, max_depth, link_url, followed_links)

def scrap_images(link: str, saved_images: set) -> int:
	count = 0
	accepted_extensions = {'.jpg', '.jpeg', '.png', '.gif', '.bmp'}
	print("\r\033[KScrapping images from '{}' ...".format(link), end='')
	response = requests.get(link)
	soup = BeautifulSoup(response.content, 'html.parser')
	for img in soup.find_all('img'):
		if img['src']:
			img_url = urljoin(response.url, img['src'])
			img_filename = os.path.basename(img_url)
			img_extension = os.path.splitext(img_filename)[1]
			if img_extension.lower() in accepted_extensions and img_filename not in saved_images:
				count += 1
				saved_images.add(img_filename)
				with open(os.path.join("data", img_filename), "wb") as file:
					file.write(requests.get(img_url).content)
	print(" Found {} images.".format(count))

def main() -> int:
	print("Crawling...")
	links = set()
	followed_links = set()
	saved_images = set()
	max_depth = 2
	followed_links.add(sys.argv[1])
	scrap_links(links, 0, max_depth, sys.argv[1], followed_links)
	print("\r\033[KScrapped {} links".format(len(links)), flush=True)
	for link in links:
		scrap_images(link, saved_images)

if (__name__ == "__main__"):
	if len(sys.argv) == 1 or len(sys.argv) > 3:
		print("Usage: python3 spider.py [-rlpS] URL")
	else:
		if not os.path.exists("data"):
			os.makedirs("data")
		main()