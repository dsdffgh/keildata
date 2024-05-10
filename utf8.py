
import os
import sys
import chardet
import codecs
from tqdm import tqdm
import warnings

def is_text_file(file_path):
    text_file_extensions = ('.txt', '.py', '.c', '.cpp', '.h', '.java', '.html', '.css', '.js', '.md', '.xml', '.json')
    return file_path.lower().endswith(text_file_extensions)

def convert_to_utf8(file_path, log):
    try:
        content = open(file_path, 'rb').read()
        source_encoding = chardet.detect(content)['encoding']
        if source_encoding is not None and source_encoding.lower() != 'utf-8':
            content = content.decode(source_encoding, 'ignore')
            with codecs.open(file_path, 'w', encoding='utf-8') as file:
                file.write(content)
            log.write(f'Converted: {file_path} from {source_encoding} to UTF-8\n')
    except PermissionError:
        print(f'Skipped: {file_path} (Permission denied)')
        log.write(f'Skipped: {file_path} (Permission denied)\n')
    except Exception as e:
        log.write(f'Error converting {file_path}: {e}\n')

def count_files(root_dir):
    count = 0
    for root, dirs, files in os.walk(root_dir):
        count += len(files)
    return count

def convert_directory(root_dir):
    log_file = 'conversion_log.txt'
    total_files = count_files(root_dir)

    with open(log_file, 'w', encoding='utf-8') as log, tqdm(total=total_files, desc='Converting files', unit='file') as progress_bar:
        
        def custom_showwarning(message, category, filename, lineno, file=None, line=None):
            log.write(f'WARNING: {message}\n')

        warnings.showwarning = custom_showwarning

        try:
            for root, dirs, files in os.walk(root_dir):
                for file in files:
                    file_path = os.path.join(root, file)
                    if not is_text_file(file_path):  # Skip non-text files
                        log.write(f'Skipped (non-text): {file_path}\n')
                        progress_bar.update(1)
                        continue

                    convert_to_utf8(file_path, log)
                    progress_bar.update(1)

        except KeyboardInterrupt:
            print("Conversion process interrupted by user.")
            log.write("Conversion process interrupted by user.\n")

if __name__ == '__main__':
    if len(sys.argv) > 1:
        root_directory = sys.argv[1]
        convert_directory(root_directory)
    else:
        print("Please provide a directory path as an argument.")
