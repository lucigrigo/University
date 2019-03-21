import unittest
import capitalise

class TestCap(unittest.TestCase):

    def test_one_word(self):
        text = 'python'
        result = capitalise.cap_text(text)
        self.assertEqual(result, 'Python')

    def test_multiple_words(self):
        text = 'monthy python'
        result = capitalise.cap_text(text)
        self.assertEqual(result, 'Monthy Python')

if __name__ == "__main__":
    unittest.main()